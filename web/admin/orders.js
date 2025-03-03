document.addEventListener('DOMContentLoaded', function() {
    // Variables globales
    const orderList = document.getElementById('orderList');
    const orderModal = document.getElementById('orderModal');
    const orderDetailsContent = document.getElementById('orderDetailsContent');
    const orderDetailsTitle = document.getElementById('orderDetailsTitle');
    const closeModal = document.querySelector('.close-modal');
    
    // Charger les commandes en attente
    loadPendingOrders();
    
    // Fonction pour formatter la date
    function formatDate(dateString) {
        if (!dateString) return 'N/A';
        const date = new Date(dateString);
        return date.toLocaleDateString('fr-FR', {
            year: 'numeric',
            month: 'short',
            day: 'numeric',
            hour: '2-digit',
            minute: '2-digit'
        });
    }
    
    // Fonction pour charger les commandes en attente depuis l'API
    function loadPendingOrders() {
        orderList.innerHTML = `
            <div class="loading">Chargement des commandes...</div>
        `;
        
        fetch('/api/admin/pending-orders')
            .then(response => response.json())
            .then(orders => {
                displayOrders(orders);
            })
            .catch(error => {
                console.error('Erreur lors du chargement des commandes:', error);
                orderList.innerHTML = `
                    <div class="empty-state">
                        <i class="fas fa-exclamation-triangle"></i>
                        <p>Erreur lors du chargement des commandes. Veuillez réessayer.</p>
                        <button class="action-btn" onclick="loadPendingOrders()">Réessayer</button>
                    </div>
                `;
            });
    }
    
    // Fonction pour afficher les commandes
    function displayOrders(orders) {
        if (orders.length === 0) {
            orderList.innerHTML = `
                <div class="empty-state">
                    <i class="fas fa-clipboard-list"></i>
                    <p>Aucune commande en attente pour le moment.</p>
                </div>
            `;
            return;
        }
        
        orderList.innerHTML = '';
        
        // Trier les commandes du plus ancien au plus récent
        orders.sort((a, b) => new Date(a.date) - new Date(b.date));
        
        orders.forEach(order => {
            const orderDate = formatDate(order.date);
            
            // Calculer le nombre total d'articles
            const totalItems = order.items.reduce((sum, item) => sum + item.quantity, 0);
            
            // Récupérer les 3 premiers noms d'articles pour l'aperçu
            const itemsPreview = order.items.slice(0, 3).map(item => {
                const shortName = item.Nom.split(' - ')[0];
                return shortName;
            }).join(', ');
            
            // Informations du client
            const userProfile = order.userProfile || {};
            const customerName = userProfile.fullName || order.userId;
            const shopName = userProfile.shopName || 'Non spécifié';
            const email = userProfile.email || 'Non spécifié';
            const phone = userProfile.phone || 'Non spécifié';
            
            const orderItem = document.createElement('div');
            orderItem.className = 'order-item';
            orderItem.innerHTML = `
                <div class="order-details">
                    <div class="order-id">
                        <i class="fas fa-shopping-cart"></i>
                        Commande #${order.orderId}
                    </div>
                    <div class="order-date">${orderDate}</div>
                    <div class="customer-info">
                        <div class="customer-name">${customerName}</div>
                        <div class="customer-shop">Boutique: ${shopName}</div>
                        <div class="customer-contact">Email: ${email} | Tél: ${phone}</div>
                    </div>
                    <div class="order-items">
                        <div class="item-count">${totalItems} article${totalItems > 1 ? 's' : ''} au total</div>
                        <div class="items-preview">${itemsPreview}${order.items.length > 3 ? '...' : ''}</div>
                    </div>
                </div>
                <div class="order-actions">
                    <button class="action-btn process-btn" data-order-id="${order.orderId}" data-user-id="${order.userId}">
                        <i class="fas fa-check"></i> Traiter commande
                    </button>
                </div>
            `;
            
            orderList.appendChild(orderItem);
        });
        
        // Ajouter les écouteurs d'événements pour les boutons de traitement
        document.querySelectorAll('.process-btn').forEach(button => {
            button.addEventListener('click', function() {
                const orderId = this.getAttribute('data-order-id');
                const userId = this.getAttribute('data-user-id');
                processOrder(orderId, userId);
            });
        });
    }
    
    // Fonction pour traiter une commande
    function processOrder(orderId, userId) {
        // Charger les détails du client
        fetch(`/api/admin/client-profile/${userId}`)
            .then(response => response.json())
            .then(clientProfile => {
                // Charger les détails de la commande
                return fetch('/api/admin/pending-orders')
                    .then(response => response.json())
                    .then(orders => {
                        const order = orders.find(o => o.orderId === orderId);
                        showProcessOrderModal(order, clientProfile);
                    });
            })
            .catch(error => {
                console.error('Erreur lors du chargement des détails:', error);
                showNotification('Erreur lors du chargement des détails', 'error');
            });
    }
    
    // Fonction pour afficher la modale de traitement de commande
    function showProcessOrderModal(order, clientProfile) {
        orderDetailsContent.innerHTML = `
            <div class="order-process-container">
                <div class="order-header">
                    <h1>Détails de la Commande #${order.orderId}</h1>
                    <span class="order-date">Commandé le ${new Date(order.date).toLocaleDateString('fr-FR', {
                        year: 'numeric', 
                        month: 'long', 
                        day: 'numeric',
                        hour: '2-digit',
                        minute: '2-digit'
                    })}</span>
                </div>

                <div class="client-info-grid">
                    <div class="client-info-card">
                        <h3>Informations Personnelles</h3>
                        <div class="info-row">
                            <strong>Nom Complet:</strong> 
                            <span>${clientProfile.firstName} ${clientProfile.lastName}</span>
                        </div>
                        <div class="info-row">
                            <strong>Email:</strong> 
                            <a href="mailto:${clientProfile.email}">${clientProfile.email}</a>
                        </div>
                        <div class="info-row">
                            <strong>Téléphone:</strong> 
                            <a href="tel:${clientProfile.phone}">${clientProfile.phone}</a>
                        </div>
                    </div>

                    <div class="client-info-card">
                        <h3>Informations de la Boutique</h3>
                        <div class="info-row">
                            <strong>Nom de la Boutique:</strong> 
                            <span>${clientProfile.shopName}</span>
                        </div>
                        <div class="info-row">
                            <strong>Adresse:</strong> 
                            <span>${clientProfile.shopAddress}, ${clientProfile.shopCity} ${clientProfile.shopZipCode}</span>
                        </div>
                        <div class="info-row">
                            <strong>Dernière Mise à Jour:</strong> 
                            <span>${new Date(clientProfile.lastUpdated).toLocaleDateString('fr-FR', {
                                year: 'numeric', 
                                month: 'long', 
                                day: 'numeric',
                                hour: '2-digit',
                                minute: '2-digit'
                            })}</span>
                        </div>
                    </div>
                </div>

                <div class="order-items-section">
                    <h2>Articles de la Commande</h2>
                    <table class="process-order-table">
                        <thead>
                            <tr>
                                <th>Article</th>
                                <th>Qty Demandé</th>
                                <th>Qty Livré</th>
                            </tr>
                        </thead>
                        <tbody>
                            ${order.items.map(item => `
                                <tr>
                                    <td>
                                        <div class="item-details">
                                            <span class="item-name">${item.Nom}</span>
                                            <span class="item-price">${parseFloat(item.prix).toFixed(2)} CHF</span>
                                        </td>
                                    <td class="quantity-cell">${item.quantity}</td>
                                    <td>
                                        <input 
                                            type="number" 
                                            min="0" 
                                            max="${item.quantity}" 
                                            value="0" 
                                            class="delivered-quantity" 
                                            data-item-name="${item.Nom}"
                                            data-item-price="${item.prix}"
                                        >
                                    </td>
                                </tr>
                            `).join('')}
                        </tbody>
                    </table>
                </div>
                
                <div class="order-summary">
                    <div class="order-total">
                        <span>Total Commande:</span>
                        <strong>${order.items.reduce((total, item) => total + (parseFloat(item.prix) * item.quantity), 0).toFixed(2)} CHF</strong>
                    </div>
                </div>
                
                <div class="order-process-actions">
                    <button class="action-btn secondary-btn cancel-btn">
                        <i class="fas fa-times"></i> Annuler
                    </button>
                    <button class="action-btn primary-btn validate-delivery" 
                            data-order-id="${order.orderId}" 
                            data-user-id="${order.userId}">
                        <i class="fas fa-check"></i> Valider la Livraison
                    </button>
                </div>
            </div>
        `;
        
        orderModal.style.display = 'block';
        
        // Gestion dynamique du total livré
        const deliveryInputs = document.querySelectorAll('.delivered-quantity');
        const orderTotal = document.querySelector('.order-total strong');
        
        deliveryInputs.forEach(input => {
            input.addEventListener('input', function() {
                let newTotal = 0;
                deliveryInputs.forEach(inp => {
                    const quantity = parseInt(inp.value, 10) || 0;
                    const price = parseFloat(inp.getAttribute('data-item-price'));
                    newTotal += quantity * price;
                });
                orderTotal.textContent = `${newTotal.toFixed(2)} CHF`;
            });
        });
        
        // Bouton annuler
        document.querySelector('.cancel-btn').addEventListener('click', () => {
            orderModal.style.display = 'none';
        });
        
        // Ajouter un écouteur pour le bouton de validation de livraison
        document.querySelector('.validate-delivery').addEventListener('click', function() {
            const orderId = this.getAttribute('data-order-id');
            const userId = this.getAttribute('data-user-id');
            
            // Récupérer les quantités livrées
            const deliveredItems = [];
            document.querySelectorAll('.delivered-quantity').forEach(input => {
                const quantity = parseInt(input.value, 10);
                if (quantity > 0) {
                    deliveredItems.push({
                        Nom: input.getAttribute('data-item-name'),
                        quantity: quantity,
                        prix: input.getAttribute('data-item-price')
                    });
                }
            });
            
            // Envoyer les données de livraison
            fetch('/api/admin/process-order', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    orderId: orderId,
                    userId: userId,
                    deliveredItems: deliveredItems
                })
            })
            .then(response => response.json())
            .then(result => {
                if (result.success) {
                    showNotification('Commande traitée avec succès', 'success');
                    orderModal.style.display = 'none';
                    loadPendingOrders();
                } else {
                    showNotification('Erreur lors du traitement de la commande', 'error');
                }
            })
            .catch(error => {
                console.error('Erreur:', error);
                showNotification('Erreur lors du traitement de la commande', 'error');
            });
        });
    }
    
    // Fonction pour afficher une notification
    function showNotification(message, type = 'success') {
        const container = document.getElementById('notification-container') || createNotificationContainer();
        
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        
        let icon = '✓';
        if (type === 'error') icon = '✕';
        if (type === 'info') icon = 'ℹ';
        
        notification.innerHTML = `
            <div class="notification-content">
                <div class="notification-icon">${icon}</div>
                <div class="notification-message">${message}</div>
            </div>
        `;
        
        container.appendChild(notification);
        
        setTimeout(() => {
            notification.style.opacity = '0';
            notification.style.transform = 'translateX(100%)';
            setTimeout(() => {
                notification.remove();
            }, 300);
        }, 3000);
    }
    
    // Fonction pour créer le conteneur de notifications si nécessaire
    function createNotificationContainer() {
        const container = document.createElement('div');
        container.id = 'notification-container';
        container.style.position = 'fixed';
        container.style.top = '20px';
        container.style.right = '20px';
        container.style.zIndex = '9999';
        document.body.appendChild(container);
        return container;
    }
    
    // Fermer la modal quand on clique sur la croix
    closeModal.addEventListener('click', function() {
        orderModal.style.display = 'none';
    });
    
    // Fermer la modal quand on clique en dehors du contenu
    window.addEventListener('click', function(event) {
        if (event.target === orderModal) {
            orderModal.style.display = 'none';
        }
    });
});