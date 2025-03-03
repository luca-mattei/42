document.addEventListener('DOMContentLoaded', function() {
    // Variables globales
    const historyOrderList = document.getElementById('historyOrderList');
    const orderModal = document.getElementById('orderModal');
    const orderDetailsContent = document.getElementById('orderDetailsContent');
    const orderDetailsTitle = document.getElementById('orderDetailsTitle');
    const closeModal = document.querySelector('.close-modal');
    const searchOrderInput = document.getElementById('searchOrderInput');
    const searchOrderBtn = document.getElementById('searchOrderBtn');
    
    // Variable pour stocker toutes les commandes chargées
    let allTreatedOrders = [];
    
    // Charger l'historique des commandes traitées
    loadTreatedOrders();
    
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
    
    // Fonction pour charger les commandes traitées depuis l'API
    function loadTreatedOrders() {
        historyOrderList.innerHTML = `
            <div class="loading">Chargement de l'historique des commandes...</div>
        `;
        
        fetch('/api/admin/treated-orders')
            .then(response => response.json())
            .then(orders => {
                // Stocker toutes les commandes pour la recherche
                allTreatedOrders = orders;
                displayHistoryOrders(orders);
            })
            .catch(error => {
                console.error('Erreur lors du chargement de l\'historique des commandes:', error);
                historyOrderList.innerHTML = `
                    <div class="empty-state">
                        <i class="fas fa-exclamation-triangle"></i>
                        <p>Erreur lors du chargement de l'historique des commandes. Veuillez réessayer.</p>
                        <button class="action-btn" onclick="loadTreatedOrders()">Réessayer</button>
                    </div>
                `;
            });
    }
    
    // Fonction pour afficher les commandes
    function displayHistoryOrders(orders) {
        if (orders.length === 0) {
            historyOrderList.innerHTML = `
                <div class="empty-state">
                    <i class="fas fa-clipboard-list"></i>
                    <p>Aucune commande traitée pour le moment.</p>
                </div>
            `;
            return;
        }
        
        historyOrderList.innerHTML = '';
        
        // Trier les commandes du plus récent au plus ancien
        orders.sort((a, b) => new Date(b.lastProcessed || b.date) - new Date(a.lastProcessed || a.date));
        
        orders.forEach(order => {
            const orderDate = formatDate(order.date);
            const processDate = formatDate(order.lastProcessed);
            
            // Calculer le nombre total d'articles livrés
            const totalDeliveredItems = order.deliveredItems 
                ? order.deliveredItems.reduce((sum, item) => sum + item.quantity, 0)
                : 0;
            
            // Récupérer les 3 premiers noms d'articles pour l'aperçu
            const itemsPreview = (order.deliveredItems || []).slice(0, 3).map(item => {
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
                        <i class="fas fa-clipboard-check"></i>
                        Commande #${order.orderId}
                    </div>
                    <div class="order-date">
                        Commandée le: ${orderDate}<br>
                        Traitée le: ${processDate}
                    </div>
                    <div class="customer-info">
                        <div class="customer-name">${customerName}</div>
                        <div class="customer-shop">Boutique: ${shopName}</div>
                        <div class="customer-contact">Email: ${email} | Tél: ${phone}</div>
                    </div>
                    <div class="order-items">
                        <div class="item-count">${totalDeliveredItems} article${totalDeliveredItems > 1 ? 's' : ''} livré${totalDeliveredItems > 1 ? 's' : ''}</div>
                        <div class="items-preview">${itemsPreview}${(order.deliveredItems || []).length > 3 ? '...' : ''}</div>
                    </div>
                </div>
                <div class="order-actions">
                    <button class="action-btn view-btn" data-order-id="${order.orderId}" data-user-id="${order.userId}">
                        <i class="fas fa-eye"></i> Voir détails
                    </button>
                    <a href="/api/admin/download-invoice/${order.orderId}/${order.userId}" class="action-btn download-btn" target="_blank">
                        <i class="fas fa-file-pdf"></i> Facture
                    </a>
                </div>
            `;
            
            historyOrderList.appendChild(orderItem);
        });
        
        // Ajouter les écouteurs d'événements pour les boutons de visualisation
        document.querySelectorAll('.view-btn').forEach(button => {
            button.addEventListener('click', function() {
                const orderId = this.getAttribute('data-order-id');
                const userId = this.getAttribute('data-user-id');
                viewOrderDetails(orderId, userId);
            });
        });
    }
    
    // Fonction pour rechercher des commandes
    function searchOrders() {
        const searchValue = searchOrderInput.value.toLowerCase().trim();
        
        if (!searchValue) {
            displayHistoryOrders(allTreatedOrders);
            return;
        }
        
        // Afficher une indication de recherche
        historyOrderList.innerHTML = `
            <div class="loading">Recherche en cours...</div>
        `;
        
        // Filtrer les commandes
        const filteredOrders = allTreatedOrders.filter(order => {
            // Recherche par ID de commande
            if (order.orderId.toLowerCase().includes(searchValue)) return true;
            
            // Recherche par ID client
            if (order.userId.toLowerCase().includes(searchValue)) return true;
            
            // Recherche par infos client
            const userProfile = order.userProfile || {};
            const fullName = (userProfile.fullName || '').toLowerCase();
            const shopName = (userProfile.shopName || '').toLowerCase();
            const email = (userProfile.email || '').toLowerCase();
            const phone = (userProfile.phone || '').toLowerCase();
            
            // Recherche par articles
            const hasMatchingItem = (order.deliveredItems || []).some(item => 
                (item.Nom || '').toLowerCase().includes(searchValue)
            );
            
            return fullName.includes(searchValue) || 
                   shopName.includes(searchValue) || 
                   email.includes(searchValue) || 
                   phone.includes(searchValue) ||
                   hasMatchingItem;
        });
        
        displayHistoryOrders(filteredOrders);
        
        // Afficher un message indiquant les résultats de recherche
        if (filteredOrders.length > 0) {
            showNotification(`${filteredOrders.length} commande(s) trouvée(s) pour "${searchValue}"`, 'info');
        } else {
            showNotification(`Aucune commande trouvée pour "${searchValue}"`, 'info');
        }
    }
    
    // Écouteur d'événement pour le bouton de recherche
    if (searchOrderBtn) {
        searchOrderBtn.addEventListener('click', searchOrders);
    }
    
    // Recherche en appuyant sur Entrée
    if (searchOrderInput) {
        searchOrderInput.addEventListener('keyup', function(event) {
            if (event.key === 'Enter') {
                searchOrders();
            }
        });
    }
    
    // Fonction pour afficher les détails d'une commande traitée
    function viewOrderDetails(orderId, userId) {
        orderDetailsContent.innerHTML = `<div class="loading">Chargement des détails...</div>`;
        orderModal.style.display = 'block';
        
        fetch(`/api/admin/order-details/${orderId}/${userId}`)
            .then(response => response.json())
            .then(orderDetails => {
                displayOrderDetails(orderDetails);
            })
            .catch(error => {
                console.error('Erreur lors du chargement des détails de la commande:', error);
                orderDetailsContent.innerHTML = `
                    <div class="empty-state">
                        <i class="fas fa-exclamation-triangle"></i>
                        <p>Erreur lors du chargement des détails de la commande.</p>
                    </div>
                `;
            });
    }
    
    // Fonction pour afficher les détails d'une commande dans la modal
    function displayOrderDetails(order) {
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
        orderDetailsTitle.textContent = `Order #${order.orderId.split('_').pop()}`;
        
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
        } else {
            detailsHTML += `
                <tr>
                    <td colspan="4" class="empty-state">Aucun article livré</td>
                </tr>
            `;
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
                    <a href="/api/admin/download-invoice/${order.orderId}/${order.userId}" class="download-invoice-btn" target="_blank">
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
        orderDetailsContent.innerHTML = detailsHTML;
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