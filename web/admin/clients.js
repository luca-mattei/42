document.addEventListener('DOMContentLoaded', function() {
    // Variables globales
    const clientTableBody = document.getElementById('clientTableBody');
    const clientModal = document.getElementById('clientModal');
    const clientDetailsContent = document.getElementById('clientDetailsContent');
    const clientDetailsTitle = document.getElementById('clientDetailsTitle');
    const searchInput = document.getElementById('searchInput');
    const searchBtn = document.getElementById('searchBtn');
    const closeModal = document.querySelector('.close-modal');
    const orderDetailsModal = document.getElementById('orderDetailsModal');
    const orderModalContent = document.getElementById('orderModalContent');
    const orderModalTitle = document.getElementById('orderModalTitle');
    
    // Fonction pour formater la date
    function formatDate(dateString) {
        if (!dateString) return 'N/A';
        const date = new Date(dateString);
        return date.toLocaleDateString('fr-CH', {
            year: 'numeric',
            month: 'short',
            day: 'numeric',
            hour: '2-digit',
            minute: '2-digit'
        });
    }
    
    // Charger la liste des clients
    loadClients();
    
    // Fonction pour charger la liste des clients
    function loadClients() {
        clientTableBody.innerHTML = `
            <tr>
                <td colspan="4" class="loading">Chargement des clients...</td>
            </tr>
        `;
        
        fetch('/api/admin/client-profiles')
            .then(response => response.json())
            .then(clients => {
                displayClients(clients);
            })
            .catch(error => {
                console.error('Erreur lors du chargement des clients:', error);
                clientTableBody.innerHTML = `
                    <tr>
                        <td colspan="4" class="loading">
                            Erreur lors du chargement des clients. Veuillez réessayer.
                            <br><button class="action-btn" onclick="loadClients()">Réessayer</button>
                        </td>
                    </tr>
                `;
            });
    }
    
    // Fonction pour afficher les clients dans le tableau
    function displayClients(clients) {
        if (clients.length === 0) {
            clientTableBody.innerHTML = `
                <tr>
                    <td colspan="4" class="empty-state">
                        <i class="fas fa-users-slash"></i>
                        <p>Aucun client trouvé.</p>
                    </td>
                </tr>
            `;
            return;
        }
        
        clientTableBody.innerHTML = '';
        
        clients.forEach(client => {
            // Récupérer l'ID du client depuis client.clientId
            const clientId = client.clientId || 'N/A';
            // Concaténer Prénom + Nom pour l'affichage (ou 'N/A' si vide)
            const fullName = `${client.firstName || ''} ${client.lastName || ''}`.trim() || 'N/A';
            const shopName = client.shopName || 'N/A';
            const email = client.email || 'N/A';
            const phone = client.phone || 'N/A';
            
            const row = document.createElement('tr');
            row.innerHTML = `
                <td>
                    <span class="client-id">${clientId}</span>
                </td>
                <td>
                    <div class="client-info">
                        <span class="client-name">${fullName}</span>
                        <span class="client-shop">${shopName}</span>
                        <div class="client-contact-mobile">
                            <a href="mailto:${email}" class="contact-link"><i class="fas fa-envelope"></i></a>
                            <a href="tel:${phone}" class="contact-link"><i class="fas fa-phone"></i></a>
                        </div>
                    </div>
                </td>
                <td>
                    <button class="action-btn view-client-btn" data-client-id="${clientId}">
                        <i class="fas fa-eye"></i> Voir détails
                    </button>
                </td>
            `;
            
            clientTableBody.appendChild(row);
        });
        
        // Ajouter les écouteurs d'événements pour les boutons "Voir détails"
        document.querySelectorAll('.view-client-btn').forEach(button => {
            button.addEventListener('click', function() {
                const clientId = this.getAttribute('data-client-id');
                viewClientDetails(clientId);
            });
        });
    }
    
    // Fonction pour afficher la fenêtre modale des détails d'un client
    function viewClientDetails(clientId) {
        // Animation de chargement dans la modal
        clientDetailsContent.innerHTML = `<div class="loading">Chargement des détails...</div>`;
        clientModal.style.display = 'block';
        
        // Charger les détails du client
        fetch('/api/admin/client-profiles')
            .then(response => response.json())
            .then(clients => {
                // On recherche le client via son clientId
                const client = clients.find(c => c.clientId === clientId);
                
                if (client) {
                    displayClientDetails(client);
                } else {
                    clientDetailsContent.innerHTML = `
                        <div class="empty-state">
                            <i class="fas fa-user-slash"></i>
                            <p>Client non trouvé</p>
                            <p>Détails recherchés : ${clientId}</p>
                        </div>
                    `;
                }
            })
            .catch(error => {
                console.error('Erreur lors du chargement des détails du client:', error);
                clientDetailsContent.innerHTML = `
                    <div class="empty-state">
                        <i class="fas fa-exclamation-triangle"></i>
                        <p>Erreur lors du chargement des détails du client</p>
                        <button class="action-btn" onclick="viewClientDetails('${clientId}')">Réessayer</button>
                    </div>
                `;
            });
    }
    
    // Fonction pour afficher les détails du client dans la modale
    function displayClientDetails(client) {
        // Mettre en titre l'ID du client
        clientDetailsTitle.textContent = `Détails du client: ${client.clientId || 'N/A'}`;
        
        // Formatter la date de dernière mise à jour
        const lastUpdated = client.lastUpdated ? formatDate(client.lastUpdated) : 'N/A';
        
        // Construire le contenu HTML pour les détails du client
        let html = `
            <div class="client-details-section">
                <h3>Informations personnelles</h3>
                <div class="client-details-grid">
                    <div class="detail-item">
                        <span class="detail-label">ID Client:</span>
                        <span class="detail-value">${client.clientId || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Prénom:</span>
                        <span class="detail-value">${client.firstName || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Nom:</span>
                        <span class="detail-value">${client.lastName || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Email:</span>
                        <span class="detail-value">${client.email || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Téléphone:</span>
                        <span class="detail-value">${client.phone || 'N/A'}</span>
                    </div>
                </div>
            </div>
            
            <div class="client-details-section">
                <h3>Informations boutique</h3>
                <div class="client-details-grid">
                    <div class="detail-item">
                        <span class="detail-label">Nom de la boutique:</span>
                        <span class="detail-value">${client.shopName || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Adresse:</span>
                        <span class="detail-value">${client.shopAddress || client.address || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Ville:</span>
                        <span class="detail-value">${client.shopCity || client.city || 'N/A'}</span>
                    </div>
                    <div class="detail-item">
                        <span class="detail-label">Code postal:</span>
                        <span class="detail-value">${client.shopZipCode || client.postalCode || 'N/A'}</span>
                    </div>
                </div>
            </div>
            
            <div class="client-details-section">
                <h3>Historique des commandes</h3>
                <div id="client-orders-container" class="client-orders-container">
                    <div class="loading">Chargement de l'historique...</div>
                </div>
            </div>
        `;
        
        // Ajouter toutes les autres informations disponibles dans une section "Métadonnées"
        html += `
            <div class="client-details-section">
                <h3>Métadonnées</h3>
                <div class="metadata">
                    <h4>Informations système</h4>
        `;
        
        // Propriétés à ignorer (déjà affichées plus haut)
        const ignoredProps = [
            'firstName', 'lastName', 'fullName', 'email', 'phone', 
            'shopName', 'shopAddress', 'shopCity', 'shopZipCode',
            'address', 'city', 'postalCode', 'username', 'id', 'clientId'
        ];
        
        // Afficher la date de dernière mise à jour si elle existe
        if (client.lastUpdated) {
            html += `<p><strong>Dernière mise à jour:</strong> ${lastUpdated}</p>`;
        }
        
        // Afficher les autres propriétés non ignorées
        for (const [key, value] of Object.entries(client)) {
            if (!ignoredProps.includes(key) && key !== 'lastUpdated') {
                let displayValue = value;
                
                // Formater selon le type
                if (typeof value === 'object' && value !== null) {
                    displayValue = JSON.stringify(value);
                } else if (typeof value === 'boolean') {
                    displayValue = value ? 'Oui' : 'Non';
                } else if (typeof value === 'string' && (value.includes('http://') || value.includes('https://'))) {
                    displayValue = `<a href="${value}" target="_blank" rel="noopener noreferrer">${value}</a>`;
                }
                
                html += `<p><strong>${key}:</strong> ${displayValue}</p>`;
            }
        }
        
        html += `
                </div>
            </div>
        `;
        
        // Mettre à jour le contenu de la modal
        clientDetailsContent.innerHTML = html;
        
        // Charger l'historique des commandes du client
        getClientOrderHistory(client.clientId)
            .then(orders => {
                const ordersContainer = document.getElementById('client-orders-container');
                displayOrderHistory(ordersContainer, orders, client.clientId);
            });
    }
    
    // Fonction pour récupérer l'historique des commandes d'un client
    function getClientOrderHistory(clientId) {
        return fetch(`/api/admin/client-orders/${clientId}`)
            .then(response => response.json())
            .catch(error => {
                console.error('Error fetching client orders:', error);
                return [];
            });
    }
    
        // Fonction pour afficher l'historique des commandes
    function displayOrderHistory(container, orders, clientId) {
        if (!orders || orders.length === 0) {
            container.innerHTML = `
                <div class="empty-state">
                    <i class="fas fa-shopping-cart"></i>
                    <p>Aucune commande pour ce client</p>
                </div>
            `;
            return;
        }
        
        // Trier les commandes par date (les plus récentes d'abord)
        orders.sort((a, b) => new Date(b.lastProcessed || b.date) - new Date(a.lastProcessed || a.date));
        
        let html = `
            <div class="client-orders-list">
                <table class="orders-table">
                    <thead>
                        <tr>
                            <th>Commande #</th>
                            <th>Date</th>
                            <th>Statut</th>
                            <th>Articles</th>
                            <th>Actions</th>
                        </tr>
                    </thead>
                    <tbody>
        `;
        
        orders.forEach(order => {
            const orderDate = formatDate(order.date);
            const processDate = order.lastProcessed ? formatDate(order.lastProcessed) : 'N/A';
            
            // Get status display
            let statusText = 'En attente';
            let statusClass = 'status-pending';
            
            // Toutes les commandes traitées (completed ou partial) sont considérées comme complètes
            if (order.status === 'completed' || order.status === 'partial') {
                statusText = 'Complète';
                statusClass = 'status-completed';
            }
            
            // Calculate total items
            const totalItems = (order.deliveredItems || order.items || []).reduce((sum, item) => sum + item.quantity, 0);
            
            html += `
                <tr>
                    <td>${order.orderId}</td>
                    <td>
                        Commandé: ${orderDate}<br>
                        ${order.lastProcessed ? `Traité: ${processDate}` : ''}
                    </td>
                    <td><span class="status-badge ${statusClass}">${statusText}</span></td>
                    <td>${totalItems} article${totalItems > 1 ? 's' : ''}</td>
                    <td class="order-actions">
            `;
            
            // Le changement se trouve dans cette section - suppression du bouton "Facture"
            if (order.status === 'pending') {
                html += `
                    <a href="/admin" class="order-action-btn">
                        <i class="fas fa-tasks"></i> Traiter
                    </a>
                `;
            } else {
                html += `
                    <button class="order-action-btn view-details-btn" data-order-id="${order.orderId}" data-client-id="${clientId}">
                        <i class="fas fa-eye"></i> Détails
                    </button>
                `;
            }
            
            html += `
                    </td>
                </tr>
            `;
        });
        
        html += `
                </tbody>
            </table>
        </div>
        `;
        
        container.innerHTML = html;
        
        // Ajouter les écouteurs d'événements pour les boutons de détails
        container.querySelectorAll('.view-details-btn').forEach(button => {
            button.addEventListener('click', function(e) {
                e.preventDefault();
                const orderId = this.getAttribute('data-order-id');
                const clientId = this.getAttribute('data-client-id');
                viewOrderDetails(orderId, clientId);
            });
        });
    }
    
    // Fonction pour afficher les détails d'une commande
    function viewOrderDetails(orderId, clientId) {
        orderModalContent.innerHTML = `<div class="loading">Chargement des détails...</div>`;
        orderDetailsModal.style.display = 'block';
        
        // Récupérer les détails de la commande
        fetch(`/api/admin/order-details/${orderId}/${clientId}`)
            .then(response => response.json())
            .then(orderDetails => {
                displayOrderDetailsModal(orderDetails, clientId);
            })
            .catch(error => {
                console.error('Erreur lors du chargement des détails de la commande:', error);
                orderModalContent.innerHTML = `
                    <div class="empty-state">
                        <i class="fas fa-exclamation-triangle"></i>
                        <p>Erreur lors du chargement des détails de la commande.</p>
                    </div>
                `;
            });
    }
    
        // Fonction pour afficher les détails de la commande dans la modal
    function displayOrderDetailsModal(order, clientId) {
        const orderModalContent = document.getElementById('orderModalContent');
        const orderModalTitle = document.getElementById('orderModalTitle');
        
        const orderDate = formatDate(order.date);
        const processDate = formatDate(order.lastProcessed);
        
        // Calculer le montant total
        const totalAmount = (order.deliveredItems || []).reduce((total, item) => {
            return total + (parseFloat(item.prix) * item.quantity);
        }, 0).toFixed(2);

        // Calculer le montant des articles en attente si présent
        let pendingTotalAmount = 0;
        if (order.remainingItems && order.remainingItems.length > 0) {
            pendingTotalAmount = order.remainingItems.reduce((total, item) => {
                return total + (parseFloat(item.prix) * item.quantity);
            }, 0).toFixed(2);
        }

        // Calculer le montant total global
        const globalTotalAmount = (parseFloat(totalAmount) + parseFloat(pendingTotalAmount)).toFixed(2);
        
        // Statut de la commande (avec option "partiellement livrée" si applicable)
        let statusText = 'COMPLETED';
        let statusClass = 'status-completed';
        
        if (order.remainingItems && order.remainingItems.length > 0) {
            statusText = 'PARTIALLY SHIPPED';
            statusClass = 'status-partial';
        }
        
        // Définir le titre de la modal - plus simple, juste Order #ID
        orderModalTitle.textContent = `Order #${order.orderId.split('_').pop()}`;
        
        // Créer le HTML pour le contenu de la modal avec un style plus proche de l'image de référence
        let detailsHTML = `
            <div class="order-header">
                <div class="order-status-indicator">
                    <span class="status-badge ${statusClass}">${statusText}</span>
                </div>
            </div>

            <div class="order-date-section">
                ${orderDate.split(',')[0]}
            </div>

            <div class="order-items-table">
                <table class="items-table">
                    <thead>
                        <tr>
                            <th class="qty-column">Qty</th>
                            <th class="product-column">Product</th>
                            <th class="unit-price-column">Unit Price</th>
                            <th class="total-column">Total</th>
                        </tr>
                    </thead>
                    <tbody>
        `;
        
        // Ajouter les articles livrés
        if (order.deliveredItems && order.deliveredItems.length > 0) {
            order.deliveredItems.forEach(item => {
                const itemTotal = (parseFloat(item.prix) * item.quantity).toFixed(2);
                
                detailsHTML += `
                    <tr>
                        <td class="qty-column">${item.quantity}</td>
                        <td class="product-column">${item.Nom}</td>
                        <td class="unit-price-column">${parseFloat(item.prix).toFixed(2)} CHF</td>
                        <td class="total-column">${itemTotal} CHF</td>
                    </tr>
                `;
            });
        }
        
        detailsHTML += `
                    </tbody>
                </table>
            </div>
        `;
        
        // Ajouter la section des articles en attente s'il y en a
        if (order.remainingItems && order.remainingItems.length > 0) {
            detailsHTML += `
                <div class="pending-items-header">
                    PENDING ITEMS
                </div>
                
                <div class="pending-items-table">
                    <table class="items-table">
                        <tbody>
            `;
            
            order.remainingItems.forEach(item => {
                const itemTotal = (parseFloat(item.prix) * item.quantity).toFixed(2);
                
                detailsHTML += `
                    <tr>
                        <td class="qty-column">${item.quantity}</td>
                        <td class="product-column">${item.Nom}</td>
                        <td class="unit-price-column">${parseFloat(item.prix).toFixed(2)} CHF</td>
                        <td class="total-column">${itemTotal} CHF</td>
                    </tr>
                `;
            });
            
            detailsHTML += `
                        </tbody>
                    </table>
                </div>
            `;
        }
        
        // Ajouter le résumé et le bouton de téléchargement
        detailsHTML += `
            <div class="order-footer">
                <div class="order-total">
                    <span>Total: ${globalTotalAmount} CHF</span>
                </div>
                <div class="download-invoice-btn-container">
                    <a href="/api/admin/download-invoice/${order.orderId}/${clientId}" class="download-invoice-btn" target="_blank">
                        <i class="fas fa-file-pdf"></i> Download Invoice
                    </a>
                </div>
            </div>
            
            <div class="client-info-section">
                <h3>Informations du client</h3>
                <div class="client-details">
                    <div class="client-detail-item">
                        <span class="detail-label">Nom:</span>
                        <span class="detail-value">${order.userProfile?.fullName || 'N/A'}</span>
                    </div>
                    <div class="client-detail-item">
                        <span class="detail-label">Email:</span>
                        <span class="detail-value">${order.userProfile?.email || 'N/A'}</span>
                    </div>
                    <div class="client-detail-item">
                        <span class="detail-label">Téléphone:</span>
                        <span class="detail-value">${order.userProfile?.phone || 'N/A'}</span>
                    </div>
                    <div class="client-detail-item">
                        <span class="detail-label">Boutique:</span>
                        <span class="detail-value">${order.userProfile?.shopName || 'N/A'}</span>
                    </div>
                    <div class="client-detail-item">
                        <span class="detail-label">Adresse:</span>
                        <span class="detail-value">${order.userProfile?.shopAddress || 'N/A'}, ${order.userProfile?.shopCity || ''} ${order.userProfile?.shopZipCode || ''}</span>
                    </div>
                </div>
            </div>
        `;
        
        // Mettre à jour le contenu de la modal
        orderModalContent.innerHTML = detailsHTML;
    }
    
    // Fermer la modal client quand on clique sur la croix
    closeModal.addEventListener('click', function() {
        clientModal.style.display = 'none';
    });
    
    // Fermer la modal quand on clique en dehors du contenu
    window.addEventListener('click', function(event) {
        if (event.target === clientModal) {
            clientModal.style.display = 'none';
        }
        if (event.target === orderDetailsModal) {
            orderDetailsModal.style.display = 'none';
        }
    });
    
    // Fermer la modal des détails de commande quand on clique sur la croix
    const closeOrderModal = document.querySelector('.close-order-modal');
    if (closeOrderModal) {
        closeOrderModal.addEventListener('click', function() {
            orderDetailsModal.style.display = 'none';
        });
    }
    
    // Fonction de recherche
    function searchClients() {
        const searchValue = searchInput.value.toLowerCase().trim();
        
        if (!searchValue) {
            loadClients();
            return;
        }
        
        // Afficher une indication de recherche
        clientTableBody.innerHTML = `
            <tr>
                <td colspan="4" class="loading">Recherche en cours...</td>
            </tr>
        `;
        
        // Récupérer tous les clients puis filtrer
        fetch('/api/admin/client-profiles')
            .then(response => response.json())
            .then(clients => {
                const filteredClients = clients.filter(client => {
                    const fullName = (`${client.firstName || ''} ${client.lastName || ''}`).toLowerCase().trim();
                    const shopName = (client.shopName || '').toLowerCase();
                    const email = (client.email || '').toLowerCase();
                    const phone = (client.phone || '').toLowerCase();
                    const username = (client.username || '').toLowerCase();
                    const city = (client.shopCity || client.city || '').toLowerCase();
                    const cId = (client.clientId || '').toLowerCase();  // Pour pouvoir chercher par ID
                    
                    return (
                        fullName.includes(searchValue) ||
                        shopName.includes(searchValue) ||
                        email.includes(searchValue) ||
                        phone.includes(searchValue) ||
                        username.includes(searchValue) ||
                        city.includes(searchValue) ||
                        cId.includes(searchValue)
                    );
                });
                
                displayClients(filteredClients);
                
                // Afficher un message indiquant les résultats de recherche
                if (filteredClients.length > 0) {
                    showNotification(`${filteredClients.length} client(s) trouvé(s) pour "${searchValue}"`, 'info');
                } else {
                    showNotification(`Aucun client trouvé pour "${searchValue}"`, 'info');
                }
            })
            .catch(error => {
                console.error('Erreur lors de la recherche:', error);
                showNotification('Erreur lors de la recherche', 'error');
            });
    }
    
    // Fonction pour afficher une notification
    function showNotification(message, type = 'success') {
        // Vérifier si le conteneur de notification existe, sinon le créer
        let container = document.getElementById('notification-container');
        if (!container) {
            container = document.createElement('div');
            container.id = 'notification-container';
            container.style.position = 'fixed';
            container.style.top = '20px';
            container.style.right = '20px';
            container.style.zIndex = '9999';
            document.body.appendChild(container);
        }
        
        // Créer la notification
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        
        // Icône selon le type
        let icon = '✓';
        if (type === 'error') icon = '✕';
        if (type === 'info') icon = 'ℹ';
        
        // Structure de la notification
        notification.innerHTML = `
            <div class="notification-content">
                <div class="notification-icon">${icon}</div>
                <div class="notification-message">${message}</div>
            </div>
        `;
        
        // Ajouter au conteneur
        container.appendChild(notification);
        
        // Supprimer après un délai
        setTimeout(() => {
            notification.style.opacity = '0';
            notification.style.transform = 'translateX(100%)';
            setTimeout(() => {
                notification.remove();
            }, 300);
        }, 3000);
    }
    
    // Écouteur d'événement pour le bouton de recherche
    if (searchBtn) {
        searchBtn.addEventListener('click', searchClients);
    }
    
    // Recherche en appuyant sur Entrée
    if (searchInput) {
        searchInput.addEventListener('keyup', function(event) {
            if (event.key === 'Enter') {
                searchClients();
            }
        });
    }
});