const express = require('express');
const session = require('express-session');
const PDFDocument = require('pdfkit');
const path = require('path');
const fs = require('fs');
const csv = require('csv-parser');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware pour parser les données des formulaires et JSON
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

// Servir les fichiers statiques
app.use(express.static('public'));
app.use('/admin', express.static('admin'));

// Configuration des sessions
app.use(session({
  secret: process.env.SESSION_SECRET || 'votre_secret_unique_ici', 
  resave: false,
  saveUninitialized: true,
  cookie: { 
    secure: process.env.NODE_ENV === 'production', 
    maxAge: 24 * 60 * 60 * 1000 // 24 heures
  }
}));

// Liste des utilisateurs avec rôles (à remplacer par une base de données en production)
const allowedUsers = [
  { username: 'admin', password: 'admin123', role: 'admin' },
  { username: 'admin2', password: 'admin124', role: 'admin' },
  { username: 'client', password: 'client123', role: 'client' },
  { username: 'client2', password: 'client123', role: 'client' },
  { username: 'luca', password: 'lumattei', role: 'client' }
];

// Middleware pour vérifier la connexion
function requireLogin(req, res, next) {
  if (!req.session.user) return res.redirect('/');
  next();
}

// Middleware spécifique pour admin
function requireAdmin(req, res, next) {
  if (req.session.user && req.session.user.role === 'admin') return next();
  res.status(403).send('Accès refusé');
}

// Vérifier si le profil est complet
function isProfileComplete(username) {
  const userProfilePath = `./data_client/${username}_profile.json`;
  
  if (!fs.existsSync(userProfilePath)) {
    return false;
  }
  
  try {
    const profileData = JSON.parse(fs.readFileSync(userProfilePath, 'utf8'));
    const requiredFields = [
      'firstName', 'lastName', 'email', 'phone', 
      'shopName', 'shopAddress', 'shopCity', 'shopZipCode'
    ];
    return requiredFields.every(field => 
      profileData[field] && profileData[field].trim() !== ''
    );
  } catch (error) {
    console.error('Erreur lors de la lecture du profil:', error);
    return false;
  }
}

// Middleware pour vérifier le profil complet
function requireCompleteProfile(req, res, next) {
  if (!req.session.user) {
    return res.redirect('/');
  }
  
  if (req.session.user.role === 'admin') {
    return next(); // Les administrateurs n'ont pas besoin de profil complet
  }
  
  if (!isProfileComplete(req.session.user.username)) {
    return res.redirect('/profile');
  }
  
  next();
}

// Fonction auxiliaire pour mettre à jour le fichier de commande legacy
function updateLegacyOrderFile(userId, orderId, updatedOrder) {
  const legacyOrdersPath = path.join(__dirname, 'data_store', `${userId}_orders.json`);
  
  if (fs.existsSync(legacyOrdersPath)) {
    try {
      // Lire le fichier existant
      const fileContent = fs.readFileSync(legacyOrdersPath, 'utf8');
      const orders = JSON.parse(fileContent);
      
      // Trouver l'index de la commande
      const orderIndex = orders.findIndex(order => 
        order.orderId === orderId || 
        (order.date === updatedOrder.date && JSON.stringify(order.items) === JSON.stringify(updatedOrder.items))
      );
      
      if (orderIndex !== -1) {
        // Mettre à jour ou remplacer la commande
        orders[orderIndex] = updatedOrder;
        
        // Enregistrer le fichier mis à jour
        fs.writeFileSync(legacyOrdersPath, JSON.stringify(orders, null, 2));
      }
    } catch (error) {
      console.error('Erreur lors de la mise à jour du fichier de commande legacy:', error);
    }
  }
}

// Fonction pour assurer que la structure de répertoires des commandes existe
function ensureUserOrderDirectories(userId) {
  // Répertoire principal des commandes de l'utilisateur
  const userOrdersDir = path.join(__dirname, 'data_store', `${userId}_orders`);
  if (!fs.existsSync(userOrdersDir)) {
    fs.mkdirSync(userOrdersDir, { recursive: true });
  }
  
  // Création des sous-répertoires
  const pendingDir = path.join(userOrdersDir, 'pending');
  const treatedDir = path.join(userOrdersDir, 'treated');
  const deliveredDir = path.join(userOrdersDir, 'delivered');
  
  [pendingDir, treatedDir, deliveredDir].forEach(dir => {
    if (!fs.existsSync(dir)) {
      fs.mkdirSync(dir, { recursive: true });
    }
  });
  
  return {
    userOrdersDir,
    pendingDir,
    treatedDir,
    deliveredDir
  };
}

// Routes principales
app.get('/', (req, res) => {
  if (req.session.user) {
    if (req.session.user.role === 'admin') {
      return res.redirect('/admin');
    } else {
      if (isProfileComplete(req.session.user.username)) {
        return res.redirect('/catalog');
      } else {
        return res.redirect('/profile');
      }
    }
  }
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Route de connexion
app.post('/login', (req, res) => {
  const { username, password } = req.body;
  const user = allowedUsers.find(u => u.username === username && u.password === password);
  
  if (user) {
    req.session.user = user;
    
    if (user.role === 'admin') {
      return res.redirect('/admin');
    } else {
      if (isProfileComplete(user.username)) {
        return res.redirect('/catalog');
      } else {
        return res.redirect('/profile');
      }
    }
  }
  
  res.status(401).send('Identifiants incorrects. <a href="/">Réessayer</a>');
});

// Route de déconnexion
app.get('/logout', (req, res) => {
  req.session.destroy(err => {
    if (err) return res.send('Erreur lors de la déconnexion');
    res.redirect('/');
  });
});

// Routes protégées
app.get('/admin', requireLogin, requireAdmin, (req, res) => {
  res.sendFile(path.join(__dirname, 'admin', 'orders.html'));
});

// Route pour la page des clients
app.get('/admin/clients', requireLogin, requireAdmin, (req, res) => {
  res.sendFile(path.join(__dirname, 'admin', 'clients.html'));
});

app.get('/catalog', requireLogin, requireCompleteProfile, (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'catalog.html'));
});

app.get('/profile', requireLogin, (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'profile.html'));
});

app.get('/orders', requireLogin, (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'orders.html'));
});

// Routes API pour le profil
app.get('/api/user-profile', requireLogin, (req, res) => {
  const userId = req.session.user.username;
  const userProfilePath = `./data_client/${userId}_profile.json`;
  
  if (fs.existsSync(userProfilePath)) {
    const fileContent = fs.readFileSync(userProfilePath, 'utf8');
    const profile = JSON.parse(fileContent);
    res.json(profile);
  } else {
    res.json({});
  }
});

app.post('/api/save-profile', requireLogin, (req, res) => {
  const userId = req.session.user.username;
  const profileData = req.body;
  
  // Ajouter un timestamp 
  profileData.lastUpdated = new Date().toISOString();
  
  // Créer le dossier data_client s'il n'existe pas
  const dataClientDir = path.join(__dirname, 'data_client');
  if (!fs.existsSync(dataClientDir)) {
    fs.mkdirSync(dataClientDir);
  }
  
  const userProfilePath = path.join(dataClientDir, `${userId}_profile.json`);
  
  // Sauvegarder le profil
  fs.writeFileSync(userProfilePath, JSON.stringify(profileData, null, 2));
  
  // Vérifier si le profil est complet
  const requiredFields = [
    'firstName', 'lastName', 'email', 'phone', 
    'shopName', 'shopAddress', 'shopCity', 'shopZipCode'
  ];
  const isComplete = requiredFields.every(field => 
    profileData[field] && profileData[field].trim() !== ''
  );
  
  res.json({ 
    success: true, 
    message: 'Profil sauvegardé avec succès',
    isProfileComplete: isComplete 
  });
});

// Route API pour récupérer les produits depuis les fichiers CSV
app.get('/api/products', (req, res) => {
  const dataFolder = path.join(__dirname, 'data');
  fs.readdir(dataFolder, (err, files) => {
    if (err) {
      console.error("Erreur lors de la lecture du dossier:", err);
      return res.status(500).send("Erreur lors de la lecture du dossier data");
    }

    const csvFiles = files.filter(file => file.endsWith('.csv'));
    let products = [];
    let filesProcessed = 0;

    if (csvFiles.length === 0) return res.json(products);

    csvFiles.forEach(file => {
      const filePath = path.join(dataFolder, file);
      const categoryName = file.replace('.csv', ''); // Ex: "pens" pour "pens.csv"

      fs.createReadStream(filePath)
        .pipe(csv({ 
          separator: ';',
          maxRows: 0 
        }))
        .on('data', (row) => {
          // Ajouter la catégorie
          row.categorie = categoryName;
          
          // Trouver l'URL d'image parmi les propriétés
          let imageUrl = null;
          
          // Parcourir toutes les propriétés pour trouver une URL d'image valide
          Object.keys(row).forEach(key => {
            const value = row[key];
            if (typeof value === 'string' && 
                (value.includes('/images/') || 
                 value.includes('/public/images/'))) {
              imageUrl = value;
            }
          });
          
          // Nettoyer l'URL d'image si nécessaire
          if (imageUrl) {
            // Enlever le préfixe '/public' s'il existe
            imageUrl = imageUrl.replace('/public', '');
            
            // S'assurer que l'URL commence par '/'
            if (!imageUrl.startsWith('/')) {
              imageUrl = '/' + imageUrl;
            }
            
            row.imageUrl = imageUrl;
          } else {
            // Image par défaut si aucune URL n'est trouvée
            row.imageUrl = `/images/${categoryName}/${categoryName}-default.jpg`;
          }
          
          // Nettoyer l'objet en supprimant les propriétés numériques ou vides
          const cleanedRow = {};
          Object.keys(row).forEach(key => {
            // Ignorer les propriétés qui sont des indices numériques ou vides
            if (isNaN(parseInt(key)) && key !== '' && row[key] !== '') {
              cleanedRow[key] = row[key];
            }
          });
          
          products.push(cleanedRow);
        })
        .on('end', () => {
          filesProcessed++;
          if (filesProcessed === csvFiles.length) {
            res.json(products);
          }
        })
        .on('error', (error) => {
          console.error(`Erreur lors de la lecture du fichier ${file}:`, error);
          filesProcessed++;
          if (filesProcessed === csvFiles.length) {
            res.json(products);
          }
        });
    });
  });
});

// Route pour sauvegarder une commande
app.post('/api/save-order', requireLogin, (req, res) => {
  const userId = req.session.user.username;
  const cartItems = req.body.items;
  const keepLegacyFormat = req.body.keepLegacyFormat || false; // Paramètre optionnel
  
  // S'assurer que les répertoires utilisateur existent
  const dirs = ensureUserOrderDirectories(userId);
  
  try {
      // Récupérer toutes les commandes en attente pour cet utilisateur
      const pendingOrderFiles = fs.readdirSync(dirs.pendingDir)
          .filter(file => file.endsWith('.json'));
      
      let combinedOrder;
      let existingOrderId;
      
      if (pendingOrderFiles.length > 0) {
          // S'il y a déjà des commandes en attente, les combiner
          const existingOrderPath = path.join(dirs.pendingDir, pendingOrderFiles[0]);
          const existingOrder = JSON.parse(fs.readFileSync(existingOrderPath, 'utf8'));
          existingOrderId = existingOrder.orderId;
          
          // Combiner les articles de la nouvelle commande avec ceux de la commande existante
          const combinedItems = [...existingOrder.items];
          
          // Pour chaque nouvel article, vérifier s'il existe déjà et l'ajouter ou mettre à jour la quantité
          cartItems.forEach(newItem => {
              const existingItemIndex = combinedItems.findIndex(item => 
                  item.Nom === newItem.Nom && item.categorie === newItem.categorie
              );
              
              if (existingItemIndex !== -1) {
                  // Si l'article existe, mettre à jour la quantité
                  combinedItems[existingItemIndex].quantity += newItem.quantity;
              } else {
                  // Sinon, ajouter le nouvel article
                  combinedItems.push(newItem);
              }
          });
          
          // Créer la commande combinée
          combinedOrder = {
              ...existingOrder,
              items: combinedItems,
              lastUpdated: new Date().toISOString()
          };
          
          // Supprimer l'ancienne commande
          fs.unlinkSync(existingOrderPath);
      } else {
          // Si pas de commande en attente, créer une nouvelle commande
          existingOrderId = `order_${Date.now()}`;
          combinedOrder = {
              orderId: existingOrderId,
              userId: userId,
              items: cartItems,
              status: 'pending',
              date: new Date().toISOString()
          };
      }
      
      // Chemin pour enregistrer la commande combinée
      const orderFilePath = path.join(dirs.pendingDir, `${existingOrderId}.json`);
      
      // Enregistrer la commande combinée
      fs.writeFileSync(orderFilePath, JSON.stringify(combinedOrder, null, 2));
      
      // Enregistrer dans le format legacy si demandé
      if (keepLegacyFormat) {
          const legacyOrdersPath = path.join(__dirname, 'data_store', `${userId}_orders.json`);
          let legacyOrders = [];
          
          if (fs.existsSync(legacyOrdersPath)) {
              // Lire le fichier existant
              const fileContent = fs.readFileSync(legacyOrdersPath, 'utf8');
              legacyOrders = JSON.parse(fileContent);
          }
          
          // Ajouter ou mettre à jour la commande
          const legacyOrderIndex = legacyOrders.findIndex(order => order.orderId === existingOrderId);
          
          if (legacyOrderIndex !== -1) {
              legacyOrders[legacyOrderIndex] = combinedOrder;
          } else {
              legacyOrders.push(combinedOrder);
          }
          
          // Enregistrer dans le fichier legacy
          fs.writeFileSync(legacyOrdersPath, JSON.stringify(legacyOrders, null, 2));
      }
      
      res.json({ 
          success: true, 
          message: pendingOrderFiles.length > 0 
              ? 'Commande mise à jour avec les nouveaux articles' 
              : 'Nouvelle commande enregistrée', 
          orderId: existingOrderId 
      });
  } catch (error) {
      console.error('Erreur lors de l\'enregistrement de la commande:', error);
      res.status(500).json({ success: false, message: 'Erreur lors de l\'enregistrement de la commande' });
  }
});

// Route pour récupérer les commandes d'un utilisateur
app.get('/api/user-orders', requireLogin, (req, res) => {
  const userId = req.session.user.username;
  const dirs = ensureUserOrderDirectories(userId);
  
  try {
    // Créer un tableau pour contenir toutes les commandes
    let allOrders = [];
    
    // Fonction pour lire les commandes d'un répertoire
    const readOrdersFromDir = (dirPath, status) => {
      if (fs.existsSync(dirPath)) {
        const files = fs.readdirSync(dirPath).filter(file => file.endsWith('.json'));
        
        files.forEach(file => {
          const orderPath = path.join(dirPath, file);
          const orderContent = fs.readFileSync(orderPath, 'utf8');
          const orderData = JSON.parse(orderContent);
          
          // Définir le statut en fonction du répertoire si pas déjà défini
          if (!orderData.status) {
            orderData.status = status;
          }
          
          allOrders.push(orderData);
        });
      }
    };
    
    // Lire depuis tous les répertoires
    readOrdersFromDir(dirs.pendingDir, 'pending');
    readOrdersFromDir(dirs.treatedDir, 'treated');
    
    // Ajouter les informations de livraison depuis le répertoire delivered
    if (fs.existsSync(dirs.deliveredDir)) {
      const invoiceFiles = fs.readdirSync(dirs.deliveredDir).filter(file => file.endsWith('.json'));
      
      invoiceFiles.forEach(file => {
        const invoicePath = path.join(dirs.deliveredDir, file);
        const invoiceContent = fs.readFileSync(invoicePath, 'utf8');
        const invoiceData = JSON.parse(invoiceContent);
        
        // Chercher la commande correspondante
        const relatedOrder = allOrders.find(order => order.orderId === invoiceData.orderId);
        
        if (relatedOrder) {
          // Ajouter les informations de livraison à la commande
          relatedOrder.deliveredInvoice = invoiceData;
        }
      });
    }
    
    // Si aucune commande trouvée dans la nouvelle structure, essayer le fichier legacy
    if (allOrders.length === 0) {
      const legacyOrdersPath = path.join(__dirname, 'data_store', `${userId}_orders.json`);
      
      if (fs.existsSync(legacyOrdersPath)) {
        const fileContent = fs.readFileSync(legacyOrdersPath, 'utf8');
        allOrders = JSON.parse(fileContent);
        
        // Migrer les commandes legacy vers la nouvelle structure (optionnel)
        allOrders.forEach(order => {
          // Générer un ID s'il n'existe pas
          if (!order.orderId) {
            order.orderId = `order_${new Date(order.date).getTime()}`;
          }
          
          // Enregistrer dans le répertoire approprié en fonction du statut
          let targetDir;
          if (order.status === 'completed' || order.status === 'partial') {
            targetDir = dirs.treatedDir;
          } else {
            targetDir = dirs.pendingDir;
          }
          
          const orderPath = path.join(targetDir, `${order.orderId}.json`);
          fs.writeFileSync(orderPath, JSON.stringify(order, null, 2));
          
          // Si la commande a été livrée, créer également une facture
          if (order.deliveredItems && order.deliveredItems.length > 0) {
            const deliveryInvoice = {
              orderId: order.orderId,
              userId: userId,
              invoiceDate: order.lastProcessed || new Date().toISOString(),
              items: order.deliveredItems,
              originalOrderDate: order.date
            };
            
            fs.writeFileSync(
              path.join(dirs.deliveredDir, `${order.orderId}_invoice.json`), 
              JSON.stringify(deliveryInvoice, null, 2)
            );
          }
        });
      }
    }
    
    // Trier les commandes par date (les plus récentes d'abord)
    allOrders.sort((a, b) => new Date(b.date) - new Date(a.date));
    
    res.json(allOrders);
  } catch (error) {
    console.error('Erreur lors de la récupération des commandes:', error);
    res.status(500).json({ error: 'Impossible de récupérer les commandes' });
  }
});

// Route pour obtenir le profil d'un client spécifique
app.get('/api/admin/client-profile/:userId', requireLogin, requireAdmin, (req, res) => {
  const userId = req.params.userId;
  const userProfilePath = path.join(__dirname, 'data_client', `${userId}_profile.json`);
  
  try {
      if (fs.existsSync(userProfilePath)) {
          const profileData = JSON.parse(fs.readFileSync(userProfilePath, 'utf8'));
          profileData.fullName = `${profileData.firstName} ${profileData.lastName}`;
          res.json(profileData);
      } else {
          res.status(404).json({ error: 'Profil client non trouvé' });
      }
  } catch (error) {
      console.error('Erreur lors de la récupération du profil:', error);
      res.status(500).json({ error: 'Erreur lors de la récupération du profil' });
  }
});

// Route admin pour traiter une commande
app.post('/api/admin/process-order', requireLogin, requireAdmin, (req, res) => {
  const { userId, orderId, deliveredItems } = req.body;
  
  if (!userId || !orderId || !Array.isArray(deliveredItems)) {
      return res.status(400).json({ error: 'Champs requis manquants ou invalides' });
  }
  
  try {
      const dirs = ensureUserOrderDirectories(userId);
      const sourcePath = path.join(dirs.pendingDir, `${orderId}.json`);
      
      // Vérifier si la commande existe
      if (!fs.existsSync(sourcePath)) {
          return res.status(404).json({ error: 'Commande non trouvée' });
      }
      
      // Lire la commande
      const orderContent = fs.readFileSync(sourcePath, 'utf8');
      const orderData = JSON.parse(orderContent);
      
      // Calculer les articles non livrés
      const remainingItems = [];
      
      orderData.items.forEach(originalItem => {
          const deliveredItem = deliveredItems.find(item => 
              item.Nom === originalItem.Nom
          );
          
          // Si l'article n'est pas dans la liste des articles livrés ou si la quantité livrée est inférieure
          if (!deliveredItem || deliveredItem.quantity < originalItem.quantity) {
              const remainingQuantity = deliveredItem 
                  ? originalItem.quantity - deliveredItem.quantity 
                  : originalItem.quantity;
                  
              remainingItems.push({
                  ...originalItem,
                  quantity: remainingQuantity
              });
          }
      });
      
      // Créer l'objet pour la commande traitée
      const treatedOrder = {
          ...orderData,
          status: remainingItems.length > 0 ? 'partial' : 'completed',
          lastProcessed: new Date().toISOString(),
          deliveredItems: deliveredItems,
          remainingItems: remainingItems
      };
      
      // Créer l'objet pour la facture de livraison
      const deliveryInvoice = {
          orderId: orderId,
          userId: userId,
          invoiceDate: new Date().toISOString(),
          items: deliveredItems,
          originalOrderDate: orderData.date
      };
      
      // Enregistrer la commande traitée
      fs.writeFileSync(
          path.join(dirs.treatedDir, `${orderId}.json`), 
          JSON.stringify(treatedOrder, null, 2)
      );
      
      // Enregistrer la facture de livraison
      fs.writeFileSync(
          path.join(dirs.deliveredDir, `${orderId}_invoice.json`), 
          JSON.stringify(deliveryInvoice, null, 2)
      );
      
      // Supprimer la commande du répertoire pending
      fs.unlinkSync(sourcePath);
      
      res.json({ 
          success: true, 
          message: 'Commande traitée avec succès',
          status: treatedOrder.status
      });
  } catch (error) {
      console.error('Erreur lors du traitement de la commande:', error);
      res.status(500).json({ error: 'Impossible de traiter la commande' });
  }
});

// Route admin pour voir toutes les commandes en attente
app.get('/api/admin/pending-orders', requireLogin, requireAdmin, (req, res) => {
  try {
    const dataStoreDir = path.join(__dirname, 'data_store');
    const userDirs = fs.readdirSync(dataStoreDir)
      .filter(item => 
        fs.statSync(path.join(dataStoreDir, item)).isDirectory() && 
        item.endsWith('_orders')
      );
    
    let pendingOrders = [];
    
    userDirs.forEach(userDir => {
      const userId = userDir.replace('_orders', '');
      const pendingDir = path.join(dataStoreDir, userDir, 'pending');
      
      if (fs.existsSync(pendingDir)) {
        const files = fs.readdirSync(pendingDir).filter(file => file.endsWith('.json'));
        
        files.forEach(file => {
          const orderPath = path.join(pendingDir, file);
          const orderContent = fs.readFileSync(orderPath, 'utf8');
          const orderData = JSON.parse(orderContent);
          
          // Ajouter l'ID utilisateur pour aider à identifier la commande
          orderData.userId = userId;
          
          // Essayer de récupérer les informations de profil utilisateur
          const userProfilePath = path.join(__dirname, 'data_client', `${userId}_profile.json`);
          if (fs.existsSync(userProfilePath)) {
            try {
              const profileContent = fs.readFileSync(userProfilePath, 'utf8');
              const profileData = JSON.parse(profileContent);
              orderData.userProfile = {
                fullName: profileData.fullName || `${profileData.firstName} ${profileData.lastName}`,
                shopName: profileData.shopName,
                email: profileData.email,
                phone: profileData.phone
              };
            } catch (error) {
              console.error(`Erreur lors de la lecture du profil pour ${userId}:`, error);
            }
          }
          
          pendingOrders.push(orderData);
        });
      }
    });
    
    // Trier les commandes par date (les plus anciennes d'abord pour traiter en FIFO)
    pendingOrders.sort((a, b) => new Date(a.date) - new Date(b.date));
    
    res.json(pendingOrders);
  } catch (error) {
    console.error('Erreur lors de la récupération des commandes en attente:', error);
    res.status(500).json({ error: 'Impossible de récupérer les commandes en attente' });
  }
});

app.get('/api/admin/client-profiles', requireLogin, requireAdmin, (req, res) => {
    const dataClientDir = path.join(__dirname, 'data_client');
    
    try {
        // Lire tous les fichiers de profil
        const profileFiles = fs.readdirSync(dataClientDir)
            .filter(file => file.endsWith('_profile.json'));
        
        const clients = profileFiles.map(file => {
            const filePath = path.join(dataClientDir, file);
            // Extraire l'ID du client avant le "_"
            const clientId = file.split('_')[0];
            
            try {
                const profileData = JSON.parse(fs.readFileSync(filePath, 'utf8'));
                profileData.clientId = clientId;  // Ajouter l'ID du fichier
                return profileData;
            } catch (error) {
                console.error(`Erreur lors de la lecture du fichier ${file}:`, error);
                return null;
            }
        }).filter(client => client !== null);
        
        res.json(clients);
    } catch (error) {
        console.error('Erreur lors de la récupération des profils de clients:', error);
        res.status(500).json({ error: 'Impossible de récupérer les profils' });
    }
});

// Configuration des répertoires de données
const dataDirs = ['./data_store', './data_client', './data'];
dataDirs.forEach(dir => {
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir);
  }
});

app.get('/api/download-invoice/:orderId', requireLogin, (req, res) => {
  const userId = req.session.user.username;
  const orderId = req.params.orderId;
  const userProfilePath = path.join(__dirname, 'data_client', `${userId}_profile.json`);
  
  // Utiliser la structure de dossiers
  const dirs = ensureUserOrderDirectories(userId);
  
  try {
    // Vérifier que le fichier de profil existe
    if (!fs.existsSync(userProfilePath)) {
      return res.status(404).json({ error: 'User profile not found' });
    }

    // Lire le profil utilisateur
    const profileContent = fs.readFileSync(userProfilePath, 'utf8');
    const userProfile = JSON.parse(profileContent);

    // Chercher la facture dans le répertoire delivered
    const invoicePath = path.join(dirs.deliveredDir, `${orderId}_invoice.json`);
    let invoiceData;
    let orderItems;
    let orderDate;
    
    // Si nous avons une facture dans le dossier delivered
    if (fs.existsSync(invoicePath)) {
      const invoiceContent = fs.readFileSync(invoicePath, 'utf8');
      invoiceData = JSON.parse(invoiceContent);
      orderItems = invoiceData.items;
      orderDate = new Date(invoiceData.invoiceDate || invoiceData.originalOrderDate);
    } 
    // Sinon, chercher dans le dossier treated pour les commandes déjà traitées
    else {
      const treatedOrderPath = path.join(dirs.treatedDir, `${orderId}.json`);
      if (fs.existsSync(treatedOrderPath)) {
        const orderContent = fs.readFileSync(treatedOrderPath, 'utf8');
        const orderData = JSON.parse(orderContent);
        
        // Si la commande est marquée comme completed ou a des items livrés
        if (orderData.status === 'completed' || 
           (orderData.deliveredItems && orderData.deliveredItems.length > 0)) {
          orderItems = orderData.deliveredItems || orderData.items;
          orderDate = new Date(orderData.lastProcessed || orderData.date);
        } else {
          return res.status(403).json({ 
            error: 'Cette commande n\'a pas encore été livrée. Aucune facture disponible.' 
          });
        }
      } else {
        // Vérifier si c'est une commande en attente
        const pendingOrderPath = path.join(dirs.pendingDir, `${orderId}.json`);
        if (fs.existsSync(pendingOrderPath)) {
          return res.status(403).json({ 
            error: 'Cette commande est en attente de traitement. Aucune facture disponible.' 
          });
        }
        
        // En dernier recours, chercher dans l'ancien format
        const legacyOrdersPath = path.join(__dirname, 'data_store', `${userId}_orders.json`);
        if (fs.existsSync(legacyOrdersPath)) {
          const fileContent = fs.readFileSync(legacyOrdersPath, 'utf8');
          const orders = JSON.parse(fileContent);
          
          // Trouver par l'ID ou par l'index
          const order = orders.find(o => o.orderId === orderId) || orders[parseInt(orderId, 10)];
          
          if (order) {
            // Vérifier si la commande a été livrée
            if (order.status === 'completed' || order.status === 'delivered' ||
               (order.deliveredItems && order.deliveredItems.length > 0)) {
              orderItems = order.deliveredItems || order.items;
              orderDate = new Date(order.lastProcessed || order.date);
            } else {
              return res.status(403).json({ 
                error: 'Cette commande n\'a pas encore été livrée. Aucune facture disponible.' 
              });
            }
          } else {
            return res.status(404).json({ error: 'Commande non trouvée' });
          }
        } else {
          return res.status(404).json({ error: 'Commande non trouvée' });
        }
      }
    }

    // Si nous n'avons pas d'éléments à facturer
    if (!orderItems || orderItems.length === 0) {
      return res.status(404).json({ error: 'Aucun élément à facturer trouvé' });
    }

    // Créer un nouveau document PDF
    const doc = new PDFDocument({ size: 'A4', margin: 50 });
    
    // Définir l'en-tête pour le téléchargement
    res.setHeader('Content-Type', 'application/pdf');
    res.setHeader(
      'Content-Disposition',
      `attachment; filename=Invoice_${userId}_${orderId}.pdf`
    );

    // Pipe du PDF directement dans la réponse
    doc.pipe(res);

    // Fonction pour ajouter un élément d'en-tête
    function addHeaderElement(doc, text, x, y, options = {}) {
      doc.font('Helvetica').fontSize(10).text(text, x, y, options);
    }

    // Logo de l'entreprise
    doc.image(path.join(__dirname, 'public', 'images', 'logo_discado_noir.png'), 50, 45, { width: 100 });

    // Informations de l'émetteur
    addHeaderElement(doc, 'Discado Sàrl', 50, 150);
    addHeaderElement(doc, 'Rue de Lausanne 7', 50, 165);
    addHeaderElement(doc, '1020 Morges, Suisse', 50, 180);
    addHeaderElement(doc, 'TVA : CHE-123.456.789', 50, 195);

    // Informations du client
    const clientY = 150;
    addHeaderElement(doc, 'Facture à :', 350, clientY);
    addHeaderElement(doc, `${userProfile.firstName} ${userProfile.lastName}`, 350, clientY + 15);
    addHeaderElement(doc, userProfile.shopName, 350, clientY + 30);
    addHeaderElement(doc, userProfile.shopAddress || userProfile.address, 350, clientY + 45);
    addHeaderElement(
      doc,
      `${userProfile.shopZipCode || userProfile.postalCode} ${userProfile.shopCity || userProfile.city}`,
      350,
      clientY + 60
    );

    // Détails de la facture
    const invoiceDate = orderDate;
    const invoiceNumber = `INV-${invoiceDate.getFullYear()}-${orderId}`;

    doc.font('Helvetica-Bold').fontSize(16).text('Facture', 50, 250);
    addHeaderElement(doc, `Numéro de facture: ${invoiceNumber}`, 50, 280);
    addHeaderElement(doc, `Date de facturation: ${invoiceDate.toLocaleDateString('fr-CH')}`, 50, 295);

    // Configuration des colonnes du tableau
    const tableTop = 350;
    const columns = [
      { title: 'Désignation',   width: 200, align: 'left' },
      { title: 'Quantité',     width:  70, align: 'center' },
      { title: 'Prix unitaire',width: 100, align: 'right' },
      { title: 'Total',        width: 100, align: 'right' }
    ];

    // Calcul de la largeur totale des colonnes
    const totalWidth = columns.reduce((sum, col) => sum + col.width, 0);

    // Position X de départ
    let currentX = 50;

    // En-tête du tableau
    doc.font('Helvetica-Bold').fontSize(10);

    columns.forEach(col => {
      doc.text(col.title, currentX, tableTop, {
        width: col.width,
        align: col.align
      });
      currentX += col.width;
    });

    // Épaisseur de trait
    doc.lineWidth(1.2);

    // Ligne séparatrice en-tête
    const lineEnd = 50 + totalWidth;
    doc.moveTo(50, tableTop + 20)
       .lineTo(lineEnd, tableTop + 20)
       .stroke();

    // Lignes d'articles
    let yPos = tableTop + 30;
    let totalHT = 0;

    orderItems.forEach(item => {
      const itemTotal = parseFloat(item.prix) * item.quantity;
      totalHT += itemTotal;

      doc.font('Helvetica').fontSize(10);

      // On réinitialise la position de départ pour chaque ligne
      let xPos = 50;

      // Désignation
      doc.text(item.Nom, xPos, yPos, {
        width: columns[0].width,
        align: columns[0].align
      });
      xPos += columns[0].width;

      // Quantité
      doc.text(String(item.quantity), xPos, yPos, {
        width: columns[1].width,
        align: columns[1].align
      });
      xPos += columns[1].width;

      // Prix unitaire
      doc.text(`${parseFloat(item.prix).toFixed(2)} CHF`, xPos, yPos, {
        width: columns[2].width,
        align: columns[2].align
      });
      xPos += columns[2].width;

      // Total
      doc.text(`${itemTotal.toFixed(2)} CHF`, xPos, yPos, {
        width: columns[3].width,
        align: columns[3].align
      });

      yPos += 20;
    });

    // Calculs et totaux
    const TVA = 0.077; // Taux de TVA suisse standard (7.7%)
    const montantTVA = totalHT * TVA;
    const totalTTC = totalHT + montantTVA;

    // Ligne séparatrice avant les totaux
    doc.moveTo(50, yPos + 10)
       .lineTo(lineEnd, yPos + 10)
       .stroke();

    // Alignement des totaux
    doc.font('Helvetica-Bold').fontSize(10);

    const col3Start = 50 + columns[0].width + columns[1].width;
    const col4Start = col3Start + columns[2].width;

    // Totaux
    doc.text('TOTAL HT', col3Start, yPos + 20, {
      width: columns[2].width,
      align: 'right'
    });
    doc.text(`${totalHT.toFixed(2)} CHF`, col4Start, yPos + 20, {
      width: columns[3].width,
      align: 'right'
    });

    doc.text('TVA 7.7%', col3Start, yPos + 40, {
      width: columns[2].width,
      align: 'right'
    });
    doc.text(`${montantTVA.toFixed(2)} CHF`, col4Start, yPos + 40, {
      width: columns[3].width,
      align: 'right'
    });

    doc.text('TOTAL TTC', col3Start, yPos + 60, {
      width: columns[2].width,
      align: 'right'
    });
    doc.text(`${totalTTC.toFixed(2)} CHF`, col4Start, yPos + 60, {
      width: columns[3].width,
      align: 'right'
    });

    // Conditions de paiement
    doc.font('Helvetica').fontSize(10);
    // doc.text('Conditions de paiement : Net 30 jours', 50, yPos + 120);
    // doc.text('Veuillez effectuer le paiement par virement bancaire', 50, yPos + 135);

    // Pied de page
    doc.text('Merci pour votre commande !', 50, yPos + 180, { align: 'center' });

    // Finaliser le PDF
    doc.end();

  } catch (error) {
    console.error('Error generating invoice:', error);
    res.status(500).json({ error: 'Could not generate invoice' });
  }
});

// Route for the Order History page
app.get('/admin/order-history', requireLogin, requireAdmin, (req, res) => {
  res.sendFile(path.join(__dirname, 'admin', 'order-history.html'));
});

// API route to get all treated orders
app.get('/api/admin/treated-orders', requireLogin, requireAdmin, (req, res) => {
  try {
    const dataStoreDir = path.join(__dirname, 'data_store');
    const userDirs = fs.readdirSync(dataStoreDir)
      .filter(item => 
        fs.statSync(path.join(dataStoreDir, item)).isDirectory() && 
        item.endsWith('_orders')
      );
    
    let treatedOrders = [];
    
    userDirs.forEach(userDir => {
      const userId = userDir.replace('_orders', '');
      const treatedDir = path.join(dataStoreDir, userDir, 'treated');
      
      if (fs.existsSync(treatedDir)) {
        const files = fs.readdirSync(treatedDir).filter(file => file.endsWith('.json'));
        
        files.forEach(file => {
          const orderPath = path.join(treatedDir, file);
          const orderContent = fs.readFileSync(orderPath, 'utf8');
          const orderData = JSON.parse(orderContent);
          
          // Ajouter l'ID utilisateur pour aider à identifier la commande
          orderData.userId = userId;
          
          // Essayer de récupérer les informations de profil utilisateur
          const userProfilePath = path.join(__dirname, 'data_client', `${userId}_profile.json`);
          if (fs.existsSync(userProfilePath)) {
            try {
              const profileContent = fs.readFileSync(userProfilePath, 'utf8');
              const profileData = JSON.parse(profileContent);
              orderData.userProfile = {
                fullName: profileData.fullName || `${profileData.firstName} ${profileData.lastName}`,
                shopName: profileData.shopName,
                email: profileData.email,
                phone: profileData.phone,
                shopAddress: profileData.shopAddress,
                shopCity: profileData.shopCity,
                shopZipCode: profileData.shopZipCode
              };
            } catch (error) {
              console.error(`Erreur lors de la lecture du profil pour ${userId}:`, error);
            }
          }
          
          treatedOrders.push(orderData);
        });
      }
    });
    
    // Trier les commandes par date de traitement (les plus récentes d'abord)
    treatedOrders.sort((a, b) => new Date(b.lastProcessed || b.date) - new Date(a.lastProcessed || a.date));
    
    res.json(treatedOrders);
  } catch (error) {
    console.error('Erreur lors de la récupération des commandes traitées:', error);
    res.status(500).json({ error: 'Impossible de récupérer les commandes traitées' });
  }
});

// API route to get details of a specific order
app.get('/api/admin/order-details/:orderId/:userId', requireLogin, requireAdmin, (req, res) => {
  const { orderId, userId } = req.params;
  
  try {
    const dirs = ensureUserOrderDirectories(userId);
    const orderPath = path.join(dirs.treatedDir, `${orderId}.json`);
    
    if (!fs.existsSync(orderPath)) {
      return res.status(404).json({ error: 'Commande non trouvée' });
    }
    
    const orderContent = fs.readFileSync(orderPath, 'utf8');
    const orderData = JSON.parse(orderContent);
    
    // Ajouter les informations de profil utilisateur
    const userProfilePath = path.join(__dirname, 'data_client', `${userId}_profile.json`);
    if (fs.existsSync(userProfilePath)) {
      try {
        const profileContent = fs.readFileSync(userProfilePath, 'utf8');
        const profileData = JSON.parse(profileContent);
        orderData.userProfile = {
          fullName: profileData.fullName || `${profileData.firstName} ${profileData.lastName}`,
          shopName: profileData.shopName,
          email: profileData.email,
          phone: profileData.phone,
          shopAddress: profileData.shopAddress,
          shopCity: profileData.shopCity,
          shopZipCode: profileData.shopZipCode
        };
      } catch (error) {
        console.error(`Erreur lors de la lecture du profil pour ${userId}:`, error);
      }
    }
    
    res.json(orderData);
  } catch (error) {
    console.error('Erreur lors de la récupération des détails de la commande:', error);
    res.status(500).json({ error: 'Impossible de récupérer les détails de la commande' });
  }
});

// API route for admin to download any invoice
app.get('/api/admin/download-invoice/:orderId/:userId', requireLogin, requireAdmin, (req, res) => {
  const { orderId, userId } = req.params;
  const userProfilePath = path.join(__dirname, 'data_client', `${userId}_profile.json`);
  
  // Utiliser la structure de dossiers
  const dirs = ensureUserOrderDirectories(userId);
  
  try {
    // Vérifier que le fichier de profil existe
    if (!fs.existsSync(userProfilePath)) {
      return res.status(404).json({ error: 'User profile not found' });
    }

    // Lire le profil utilisateur
    const profileContent = fs.readFileSync(userProfilePath, 'utf8');
    const userProfile = JSON.parse(profileContent);

    // Chercher la facture dans le répertoire delivered
    const invoicePath = path.join(dirs.deliveredDir, `${orderId}_invoice.json`);
    let invoiceData;
    let orderItems;
    let orderDate;
    
    // Si nous avons une facture dans le dossier delivered
    if (fs.existsSync(invoicePath)) {
      const invoiceContent = fs.readFileSync(invoicePath, 'utf8');
      invoiceData = JSON.parse(invoiceContent);
      orderItems = invoiceData.items;
      orderDate = new Date(invoiceData.invoiceDate || invoiceData.originalOrderDate);
    } 
    // Sinon, chercher dans le dossier treated pour les commandes déjà traitées
    else {
      const treatedOrderPath = path.join(dirs.treatedDir, `${orderId}.json`);
      if (fs.existsSync(treatedOrderPath)) {
        const orderContent = fs.readFileSync(treatedOrderPath, 'utf8');
        const orderData = JSON.parse(orderContent);
        
        // Si la commande est marquée comme completed ou a des items livrés
        if (orderData.status === 'completed' || 
           (orderData.deliveredItems && orderData.deliveredItems.length > 0)) {
          orderItems = orderData.deliveredItems || orderData.items;
          orderDate = new Date(orderData.lastProcessed || orderData.date);
        } else {
          return res.status(403).json({ 
            error: 'Cette commande n\'a pas encore été livrée. Aucune facture disponible.' 
          });
        }
      } else {
        return res.status(404).json({ error: 'Commande non trouvée' });
      }
    }

    // Si nous n'avons pas d'éléments à facturer
    if (!orderItems || orderItems.length === 0) {
      return res.status(404).json({ error: 'Aucun élément à facturer trouvé' });
    }

    // Créer un nouveau document PDF
    const doc = new PDFDocument({ size: 'A4', margin: 50 });
    
    // Définir l'en-tête pour le téléchargement
    res.setHeader('Content-Type', 'application/pdf');
    res.setHeader(
      'Content-Disposition',
      `attachment; filename=Invoice_${userId}_${orderId}.pdf`
    );

    // Pipe du PDF directement dans la réponse
    doc.pipe(res);

    // Fonction pour ajouter un élément d'en-tête
    function addHeaderElement(doc, text, x, y, options = {}) {
      doc.font('Helvetica').fontSize(10).text(text, x, y, options);
    }

    // Logo de l'entreprise
    doc.image(path.join(__dirname, 'public', 'images', 'logo_discado_noir.png'), 50, 45, { width: 100 });

    // Informations de l'émetteur
    addHeaderElement(doc, 'Discado Sàrl', 50, 150);
    addHeaderElement(doc, 'Rue de Lausanne 7', 50, 165);
    addHeaderElement(doc, '1020 Morges, Suisse', 50, 180);
    addHeaderElement(doc, 'TVA : CHE-123.456.789', 50, 195);

    // Informations du client
    const clientY = 150;
    addHeaderElement(doc, 'Facture à :', 350, clientY);
    addHeaderElement(doc, `${userProfile.firstName} ${userProfile.lastName}`, 350, clientY + 15);
    addHeaderElement(doc, userProfile.shopName, 350, clientY + 30);
    addHeaderElement(doc, userProfile.shopAddress || userProfile.address, 350, clientY + 45);
    addHeaderElement(
      doc,
      `${userProfile.shopZipCode || userProfile.postalCode} ${userProfile.shopCity || userProfile.city}`,
      350,
      clientY + 60
    );

    // Détails de la facture
    const invoiceDate = orderDate;
    const invoiceNumber = `INV-${invoiceDate.getFullYear()}-${orderId}`;

    doc.font('Helvetica-Bold').fontSize(16).text('Facture', 50, 250);
    addHeaderElement(doc, `Numéro de facture: ${invoiceNumber}`, 50, 280);
    addHeaderElement(doc, `Date de facturation: ${invoiceDate.toLocaleDateString('fr-CH')}`, 50, 295);

    // Configuration des colonnes du tableau
    const tableTop = 350;
    const columns = [
      { title: 'Désignation',   width: 200, align: 'left' },
      { title: 'Quantité',     width:  70, align: 'center' },
      { title: 'Prix unitaire',width: 100, align: 'right' },
      { title: 'Total',        width: 100, align: 'right' }
    ];

    // Calcul de la largeur totale des colonnes
    const totalWidth = columns.reduce((sum, col) => sum + col.width, 0);

    // Position X de départ
    let currentX = 50;

    // En-tête du tableau
    doc.font('Helvetica-Bold').fontSize(10);

    columns.forEach(col => {
      doc.text(col.title, currentX, tableTop, {
        width: col.width,
        align: col.align
      });
      currentX += col.width;
    });

    // Épaisseur de trait
    doc.lineWidth(1.2);

    // Ligne séparatrice en-tête
    const lineEnd = 50 + totalWidth;
    doc.moveTo(50, tableTop + 20)
       .lineTo(lineEnd, tableTop + 20)
       .stroke();

    // Lignes d'articles
    let yPos = tableTop + 30;
    let totalHT = 0;

    orderItems.forEach(item => {
      const itemTotal = parseFloat(item.prix) * item.quantity;
      totalHT += itemTotal;

      doc.font('Helvetica').fontSize(10);

      // On réinitialise la position de départ pour chaque ligne
      let xPos = 50;

      // Désignation
      doc.text(item.Nom, xPos, yPos, {
        width: columns[0].width,
        align: columns[0].align
      });
      xPos += columns[0].width;

      // Quantité
      doc.text(String(item.quantity), xPos, yPos, {
        width: columns[1].width,
        align: columns[1].align
      });
      xPos += columns[1].width;

      // Prix unitaire
      doc.text(`${parseFloat(item.prix).toFixed(2)} CHF`, xPos, yPos, {
        width: columns[2].width,
        align: columns[2].align
      });
      xPos += columns[2].width;

      // Total
      doc.text(`${itemTotal.toFixed(2)} CHF`, xPos, yPos, {
        width: columns[3].width,
        align: columns[3].align
      });

      yPos += 20;
    });

    // Calculs et totaux
    const TVA = 0.077; // Taux de TVA suisse standard (7.7%)
    const montantTVA = totalHT * TVA;
    const totalTTC = totalHT + montantTVA;

    // Ligne séparatrice avant les totaux
    doc.moveTo(50, yPos + 10)
       .lineTo(lineEnd, yPos + 10)
       .stroke();

    // Alignement des totaux
    doc.font('Helvetica-Bold').fontSize(10);

    const col3Start = 50 + columns[0].width + columns[1].width;
    const col4Start = col3Start + columns[2].width;

    // Totaux
    doc.text('TOTAL HT', col3Start, yPos + 20, {
      width: columns[2].width,
      align: 'right'
    });
    doc.text(`${totalHT.toFixed(2)} CHF`, col4Start, yPos + 20, {
      width: columns[3].width,
      align: 'right'
    });

    doc.text('TVA 7.7%', col3Start, yPos + 40, {
      width: columns[2].width,
      align: 'right'
    });
    doc.text(`${montantTVA.toFixed(2)} CHF`, col4Start, yPos + 40, {
      width: columns[3].width,
      align: 'right'
    });

    doc.text('TOTAL TTC', col3Start, yPos + 60, {
      width: columns[2].width,
      align: 'right'
    });
    doc.text(`${totalTTC.toFixed(2)} CHF`, col4Start, yPos + 60, {
      width: columns[3].width,
      align: 'right'
    });

    // Pied de page
    doc.font('Helvetica').fontSize(10);
    doc.text('Merci pour votre commande !', 50, yPos + 180, { align: 'center' });

    // Finaliser le PDF
    doc.end();

  } catch (error) {
    console.error('Error generating invoice:', error);
    res.status(500).json({ error: 'Could not generate invoice' });
  }
});

// Add this route to your index.js file

// API route to get all orders for a specific client
app.get('/api/admin/client-orders/:clientId', requireLogin, requireAdmin, (req, res) => {
  const clientId = req.params.clientId;
  
  try {
    const dirs = ensureUserOrderDirectories(clientId);
    let clientOrders = [];
    
    // Get treated orders
    if (fs.existsSync(dirs.treatedDir)) {
      const treatedFiles = fs.readdirSync(dirs.treatedDir).filter(file => file.endsWith('.json'));
      
      treatedFiles.forEach(file => {
        const orderPath = path.join(dirs.treatedDir, file);
        const orderContent = fs.readFileSync(orderPath, 'utf8');
        const orderData = JSON.parse(orderContent);
        
        clientOrders.push(orderData);
      });
    }
    
    // Get pending orders
    if (fs.existsSync(dirs.pendingDir)) {
      const pendingFiles = fs.readdirSync(dirs.pendingDir).filter(file => file.endsWith('.json'));
      
      pendingFiles.forEach(file => {
        const orderPath = path.join(dirs.pendingDir, file);
        const orderContent = fs.readFileSync(orderPath, 'utf8');
        const orderData = JSON.parse(orderContent);
        
        clientOrders.push(orderData);
      });
    }
    
    // Check for legacy orders (backward compatibility)
    const legacyOrdersPath = path.join(__dirname, 'data_store', `${clientId}_orders.json`);
    if (fs.existsSync(legacyOrdersPath)) {
      const fileContent = fs.readFileSync(legacyOrdersPath, 'utf8');
      const legacyOrders = JSON.parse(fileContent);
      
      // Add any legacy orders that aren't already included
      legacyOrders.forEach(legacyOrder => {
        const isDuplicate = clientOrders.some(order => 
          order.orderId === legacyOrder.orderId ||
          (order.date === legacyOrder.date && JSON.stringify(order.items) === JSON.stringify(legacyOrder.items))
        );
        
        if (!isDuplicate) {
          clientOrders.push(legacyOrder);
        }
      });
    }
    
    // Sort orders by date (newest first)
    clientOrders.sort((a, b) => new Date(b.date) - new Date(a.date));
    
    res.json(clientOrders);
  } catch (error) {
    console.error('Erreur lors de la récupération des commandes du client:', error);
    res.status(500).json({ error: 'Impossible de récupérer les commandes du client' });
  }
});

// Lancement du serveur
app.listen(PORT, '0.0.0.0', () => {
  console.log(`Serveur démarré sur http://localhost:${PORT}`);
  console.log(`Accessible sur le réseau à l'adresse 192.168.1.232:${PORT}`);
});