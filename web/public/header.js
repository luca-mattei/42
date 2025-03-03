// Header and menu functionality
document.addEventListener('DOMContentLoaded', function() {
    // References to UI elements
    const menuToggle = document.getElementById('menuToggle');
    const dropdownMenu = document.getElementById('dropdownMenu');
    const menuOverlay = document.getElementById('menuOverlay');
    const userMenuToggle = document.getElementById('userMenuToggle');
    const userMenu = document.getElementById('userMenu');
    const categoryItems = document.querySelectorAll('.category-item');
    const header = document.querySelector('header');
    const cartToggle = document.getElementById('cartToggle');
    const cartModal = document.getElementById('cart-modal');
    
    // Toggle menu when menu button is clicked
    if (menuToggle) {
        menuToggle.addEventListener('click', function() {
            dropdownMenu.classList.toggle('open');
            menuOverlay.classList.toggle('active');
            
            // Close user menu if it's open
            if (userMenu && userMenu.classList.contains('open')) {
                userMenu.classList.remove('open');
            }
        });
    }
    
    // Toggle user menu when user button is clicked
    if (userMenuToggle && userMenu) {
        userMenuToggle.addEventListener('click', function() {
            userMenu.classList.toggle('open');
            
            // Close main menu if it's open
            if (dropdownMenu && dropdownMenu.classList.contains('open')) {
                dropdownMenu.classList.remove('open');
                menuOverlay.classList.remove('active');
            }
        });
    }
    
    // Open cart modal
    if (cartToggle && cartModal) {
        cartToggle.addEventListener('click', function() {
            // Call existing function to display cart contents
            if (typeof displayCart === 'function') {
                displayCart();
            }
            
            cartModal.style.display = 'block';
            
            // Close menus if open
            if (dropdownMenu && dropdownMenu.classList.contains('open')) {
                dropdownMenu.classList.remove('open');
                menuOverlay.classList.remove('active');
            }
            
            if (userMenu && userMenu.classList.contains('open')) {
                userMenu.classList.remove('open');
            }
        });
    }
    
    // Close menus when clicking outside
    if (menuOverlay) {
        menuOverlay.addEventListener('click', function() {
            if (dropdownMenu) {
                dropdownMenu.classList.remove('open');
            }
            menuOverlay.classList.remove('active');
        });
    }
    
    // Category selection
    if (categoryItems.length > 0) {
        categoryItems.forEach(item => {
            item.addEventListener('click', function() {
                // Remove active class from all items
                categoryItems.forEach(i => i.classList.remove('active'));
                
                // Add active class to clicked item
                this.classList.add('active');
                
                // Get category value and filter products
                const category = this.getAttribute('data-category');
                
                // Update the category filter select if it exists
                const categoryFilter = document.getElementById('categoryFilter');
                if (categoryFilter) {
                    categoryFilter.value = category;
                    
                    // Trigger the change event to filter products
                    const event = new Event('change');
                    categoryFilter.dispatchEvent(event);
                }
                
                // Close the menu after selection
                if (dropdownMenu) {
                    dropdownMenu.classList.remove('open');
                }
                if (menuOverlay) {
                    menuOverlay.classList.remove('active');
                }
            });
        });
    }
    
    // Compact header on scroll
    if (header) {
        let lastScrollTop = 0;
        window.addEventListener('scroll', function() {
            const currentScrollTop = window.pageYOffset || document.documentElement.scrollTop;
            
            // Make header compact when scrolling down
            if (currentScrollTop > 50) {
                header.classList.add('header-compact');
            } else {
                header.classList.remove('header-compact');
            }
            
            // Hide header when scrolling down, show when scrolling up
            if (currentScrollTop > lastScrollTop && currentScrollTop > 200) {
                header.style.transform = 'translateY(-100%)';
            } else {
                header.style.transform = 'translateY(0)';
            }
            
            lastScrollTop = currentScrollTop;
        });
    }
    
    // Update cart count badge on load
    updateHeaderCartCount();
});

// Update cart count in the header
function updateHeaderCartCount() {
    const cart = JSON.parse(localStorage.getItem('cart')) || [];
    const cartCount = cart.reduce((total, item) => total + item.quantity, 0);
    const cartCountBadge = document.getElementById('cartCountBadge');
    
    if (cartCountBadge) {
        cartCountBadge.textContent = cartCount;
        cartCountBadge.style.display = cartCount > 0 ? 'flex' : 'none';
    }
}

// Function to be called when cart is updated
function updateCartUI() {
    // Update cart count in header
    updateHeaderCartCount();
    
    // Also update existing cart count if present
    const cartCountElement = document.querySelector('.cart-count');
    if (cartCountElement) {
        const cart = JSON.parse(localStorage.getItem('cart')) || [];
        const cartCount = cart.reduce((total, item) => total + item.quantity, 0);
        cartCountElement.textContent = cartCount;
    }
}

document.addEventListener('DOMContentLoaded', function() {
    const pdfCatalogToggle = document.getElementById('pdfCatalogToggle');
    if (pdfCatalogToggle) {
      pdfCatalogToggle.addEventListener('click', function() {
        // Modifier le lien Dropbox pour un téléchargement direct
        const catalogPath = 'https://www.dropbox.com/scl/fi/0gymxq4jtwdno6q1l5td2/Catalogue-Discado-2025.pdf?rlkey=zx8p1syhojya62atiteib8660&e=1&st=ol0xk3lc&dl=1';
        
        // Ouvrir le lien dans un nouvel onglet
        window.open(catalogPath, '_blank');
      });
    }
  });

// Add cart update function to window for compatibility with existing code
window.updateHeaderCartCount = updateHeaderCartCount;
window.updateCartUI = updateCartUI;
