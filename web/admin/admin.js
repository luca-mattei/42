/**
 * Script principal pour le panel d'administration
 * Gère les onglets, les modales et les notifications
 */
document.addEventListener('DOMContentLoaded', function() {
    console.log('Admin panel initialized');
    
    // Gestion des onglets
    initTabs();
    
    // Gestion des modales
    initModals();
    
    // Charger les données du premier onglet (commandes)
    loadPendingOrders();
});

/**
 * Initialise les onglets et leur comportement
 */
function initTabs() {
    const tabBtns = document.querySelectorAll('.tab-btn');
    const tabContents = document.querySelectorAll('.tab-content');
    
    tabBtns.forEach(btn => {
        btn.addEventListener('click', function() {
            // Désactiver tous les onglets
            tabBtns.forEach(b => b.classList.remove('active'));
            tabContents.forEach(content => content.classList.remove('active'));
            
            // Activer l'onglet cliqué
            this.classList.add('active');
            
            // Afficher le contenu correspondant
            const tabId = this.getAttribute('data-tab');
            const tabContent = document.getElementById(`${tabId}-tab`);
            if (tabContent) {
                tabContent.classList.add('active');
            }
            
            // Charger les données appropriées
            if (tabId === 'orders') {
                loadPendingOrders();
            } else if (tabId === 'clients') {
                loadClientData();
            }
        });
    });
}

/**
 * Initialise les modales et leur comportement
 */
function initModals() {
    const modals = document.querySelectorAll('.modal');
    const closeButtons = document.querySelectorAll('.close-modal, .close-btn');
    
    // Fermer la modale quand on clique sur le bouton de fermeture
    closeButtons.forEach(button => {
        button.addEventListener('click', function() {
            modals.forEach(modal => {
                modal.style.display = 'none';
            });
        });
    });
    
    // Fermer la modale quand on clique en dehors du contenu
    window.addEventListener('click', function(event) {
        modals.forEach(modal => {
            if (event.target === modal) {
                modal.style.display = 'none';
            }
        });
    });
}

/**
 * Affiche une notification
 * @param {string} message - Le message à afficher
 * @param {string} type - Le type de notification ('success', 'error', 'info')
 */
function showNotification(message, type = 'success') {
    const container = document.getElementById('notification-container');
    
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

// Rendre les fonctions accessibles globalement
window.showNotification = showNotification;