async function fetchProducts() {
    try {
        const response = await fetch('/api/products');
        const products = await response.json();
        return products;
    } catch (error) {
        console.error("Erreur lors de la récupération des produits:", error);
        return [];
    }
}

// Fonction pour afficher une notification
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
        <div class="notification-progress">
            <div class="notification-progress-bar"></div>
        </div>
    `;
    
    // Ajouter au conteneur
    container.appendChild(notification);
    
    // Supprimer après l'animation
    setTimeout(() => {
        notification.remove();
    }, 4000);
}

// Tableau temporaire pour stocker les produits que l'utilisateur souhaite ajouter
let selectedProducts = [];

// This function needs to be updated to remove the plus/minus buttons
function displayProducts(products, category = "all") {
    const list = document.getElementById("productList");
    list.innerHTML = "";

    products
        .filter(p => category === "all" || p.categorie === category)
        .filter(p => p.Nom && p.Nom.trim() !== "")
        .forEach((p, index) => {
            // Vérifier si les propriétés essentielles existent, sinon utiliser des valeurs par défaut
            const productName = p.Nom || "Produit sans nom";
            const productPrice = p.prix || "0.00";
            const productCategory = p.categorie || "default";
            const productImage = p.imageUrl || `/images/${productCategory}/${productCategory}-default.jpg`;

            const li = document.createElement("li");
            li.className = "product-item";
            // Ajouter un attribut data-product-id pour identifier le produit
            li.setAttribute('data-product-id', p.id || index);

            // Image du produit
            const imgContainer = document.createElement("div");
            imgContainer.className = "product-img-container";
            
            const img = document.createElement("img");
            img.src = productImage;
            img.alt = productName;
            img.className = "product-img";
            
            // Ajouter l'attribut data-high-res pour l'image en haute résolution
            img.setAttribute('data-high-res', productImage);
            
            // Gestion plus robuste des erreurs d'images
            img.onerror = function() {
                console.log(`Image non trouvée: ${this.src}`);
                // Essayer d'abord avec un chemin sans /public
                if (this.src.includes('/public/')) {
                    this.src = this.src.replace('/public/', '/');
                    this.setAttribute('data-high-res', this.src); // Mettre à jour l'attribut high-res aussi
                    return;
                }
                
                // Fallback vers une image par défaut en cas d'erreur
                this.src = `/images/${productCategory}/${productCategory}-default.jpg`;
                this.setAttribute('data-high-res', this.src); // Mettre à jour l'attribut high-res aussi
                
                // Deuxième fallback si l'image par défaut de catégorie n'existe pas
                this.onerror = function() {
                    this.src = '/images/product-default.jpg';
                    this.setAttribute('data-high-res', this.src); // Mettre à jour l'attribut high-res aussi
                    // Éviter les boucles infinies
                    this.onerror = null;
                };
            };
            
            imgContainer.appendChild(img);

            // Conteneur d'informations (nom et prix)
            const infoContainer = document.createElement("div");
            infoContainer.className = "product-info";

            // Nom du produit
            const nameSpan = document.createElement("span");
            nameSpan.textContent = productName;
            nameSpan.className = "product-name";

            // Prix du produit
            const priceSpan = document.createElement("span");
            priceSpan.textContent = `${productPrice} CHF`;
            priceSpan.className = "product-price";

            infoContainer.appendChild(nameSpan);
            infoContainer.appendChild(priceSpan);

            // Conteneur pour le compteur
            const actionContainer = document.createElement("div");
            actionContainer.className = "product-actions";

            // Conteneur de quantité - SIMPLIFIÉ SANS BOUTONS PLUS/MOINS
            const quantityContainer = document.createElement("div");
            quantityContainer.className = "quantity-container";

            // Input pour la quantité
            const quantityInput = document.createElement("input");
            quantityInput.type = "text"; // Utiliser "text" au lieu de "number"
            quantityInput.inputMode = "numeric"; // Affiche le clavier numérique
            quantityInput.pattern = "[0-9]*"; // Force la saisie de chiffres uniquement
            quantityInput.min = "0";
            quantityInput.value = "0";
            quantityInput.className = "quantity-input simplified";

            // Effacer automatiquement le "0" lorsque l'utilisateur clique sur le champ
            quantityInput.addEventListener('focus', function() {
                if (this.value === "0") {
                    this.value = "";
                }
            });

            // Remettre "0" si l'utilisateur quitte le champ sans rien saisir
            quantityInput.addEventListener('blur', function() {
                if (this.value === "") {
                    this.value = "0";
                }
            });

            // Permettre l'ajout au panier avec Enter
            quantityInput.addEventListener('keyup', function(event) {
                if (event.key === 'Enter') {
                    const addBtn = this.closest('.product-actions').querySelector('.add-to-cart-btn');
                    if (addBtn) {
                        addBtn.click();
                    }
                }
            });
            
            // Mise à jour du tableau selectedProducts quand la quantité change
            quantityInput.addEventListener('change', function() {
                updateSelectedProducts(p, parseInt(this.value) || 0, productImage);
            });

            // Ajout des éléments au conteneur de quantité - SEULEMENT L'INPUT
            quantityContainer.appendChild(quantityInput);

            // Ajout des éléments au conteneur d'actions
            actionContainer.appendChild(quantityContainer);

            // Ajout de tous les éléments à l'élément de liste
            li.appendChild(imgContainer);
            li.appendChild(infoContainer);
            li.appendChild(actionContainer);

            list.appendChild(li);
        });
    
    // Déclencher un événement indiquant que les produits ont été chargés
    document.dispatchEvent(new CustomEvent('productsLoaded'));
}

// Mise à jour de la fonction pour ajouter au panier pour gérer l'absence des boutons +/-
function updateSelectedProducts(product, quantity, imageUrl) {
    // S'assurer que la quantité est un nombre, avec 0 comme valeur par défaut
    quantity = parseInt(quantity) || 0;
    
    // Vérifier si le produit est déjà dans le tableau
    const existingProductIndex = selectedProducts.findIndex(item => 
        item.Nom === product.Nom && item.categorie === product.categorie
    );
    
    if (quantity <= 0) {
        // Si la quantité est 0 ou négative, supprimer du tableau si présent
        if (existingProductIndex !== -1) {
            selectedProducts.splice(existingProductIndex, 1);
        }
    } else {
        if (existingProductIndex !== -1) {
            // Mettre à jour la quantité si le produit existe déjà
            selectedProducts[existingProductIndex].quantity = quantity;
        } else {
            // Ajouter le nouveau produit au tableau
            selectedProducts.push({
                ...product,
                quantity: quantity,
                imageUrl: imageUrl
            });
        }
    }
    
    // Mettre à jour le compteur sur le bouton flottant
    updateFloatingButtonCounter();
}

// Fonction pour mettre à jour le compteur sur le bouton flottant
function updateFloatingButtonCounter() {
    const totalItems = selectedProducts.reduce((total, item) => total + item.quantity, 0);
    const counterElement = document.getElementById('floatingButtonCounter');
    if (counterElement) {
        counterElement.textContent = totalItems;
        
        // Afficher ou masquer le compteur en fonction du nombre d'articles
        if (totalItems > 0) {
            counterElement.style.display = 'flex';
        } else {
            counterElement.style.display = 'none';
        }
    }
}

// Fonction pour ajouter au panier
function addToCart(product, quantity, imageUrl) {
    console.log(`Ajout de ${quantity} ${product.Nom} au panier`);
    
    // Récupérer le panier actuel du localStorage ou créer un nouveau
    let cart = JSON.parse(localStorage.getItem('cart')) || [];
    
    // Vérifier si le produit est déjà dans le panier
    const existingProductIndex = cart.findIndex(item => 
        item.Nom === product.Nom && item.categorie === product.categorie
    );
    
    if (existingProductIndex !== -1) {
        // Mettre à jour la quantité si le produit existe déjà
        cart[existingProductIndex].quantity += quantity;
    } else {
        // Ajouter le nouveau produit au panier
        cart.push({
            ...product,
            quantity: quantity,
            imageUrl: imageUrl
        });
    }
    
    // Sauvegarder dans localStorage
    localStorage.setItem('cart', JSON.stringify(cart));
    
    // Afficher une notification au lieu d'une alerte
    showNotification(`${quantity} × ${product.Nom} added to cart !`, 'success');
}

// Fonction pour ajouter tous les produits sélectionnés au panier
function addAllSelectedToCart() {
    if (selectedProducts.length === 0) {
        showNotification('Please select at least one product', 'info');
        return;
    }
    
    // Récupérer le panier actuel du localStorage
    let cart = JSON.parse(localStorage.getItem('cart')) || [];
    
    // Ajouter chaque produit sélectionné au panier
    selectedProducts.forEach(product => {
        // Vérifier si le produit est déjà dans le panier
        const existingProductIndex = cart.findIndex(item => 
            item.Nom === product.Nom && item.categorie === product.categorie
        );
        
        if (existingProductIndex !== -1) {
            // Mettre à jour la quantité si le produit existe déjà
            cart[existingProductIndex].quantity += product.quantity;
        } else {
            // Ajouter le nouveau produit au panier
            cart.push({...product});
        }
    });
    
    // Sauvegarder le panier mis à jour
    localStorage.setItem('cart', JSON.stringify(cart));
    
    // Afficher une notification
    const totalItems = selectedProducts.reduce((total, item) => total + item.quantity, 0);
    showNotification(`${totalItems} items added to cart!`, 'success');
    
    // Réinitialiser toutes les quantités à zéro
    resetAllQuantities();
    
    // Mettre à jour le compteur du panier
    updateCartCount();
    
    // Mettre à jour le badge du panier dans le header
    if (typeof updateCartUI === 'function') {
        updateCartUI();
    }
}

// Fonction pour réinitialiser toutes les quantités à zéro
function resetAllQuantities() {
    // Réinitialiser les champs d'entrée
    document.querySelectorAll('.quantity-input').forEach(input => {
        input.value = "0";
    });
    
    // Vider le tableau des produits sélectionnés
    selectedProducts = [];
    
    // Mettre à jour le compteur sur le bouton flottant
    updateFloatingButtonCounter();
}

// Fonction pour mettre à jour l'affichage du nombre d'articles dans le panier
function updateCartCount() {
    const cart = JSON.parse(localStorage.getItem('cart')) || [];
    const cartCount = cart.reduce((total, item) => total + item.quantity, 0);
    
    // Mettre à jour le badge du compteur sur l'icône du panier
    const cartCountBadge = document.getElementById('cartCountBadge');
    if (cartCountBadge) {
        cartCountBadge.textContent = cartCount;
    }
    
    // Compatibilité avec l'ancien code
    const cartCountElement = document.querySelector('.cart-count');
    if (cartCountElement) {
        cartCountElement.textContent = cartCount;
    }
    
    // Mettre à jour le compteur dans le header aussi
    if (typeof updateHeaderCartCount === 'function') {
        updateHeaderCartCount();
    }
}

// Fonction pour afficher le contenu du panier dans la modale
function displayCart() {
    const cartItemsContainer = document.getElementById('cart-items');
    const cart = JSON.parse(localStorage.getItem('cart')) || [];
    
    cartItemsContainer.innerHTML = '';
    
    let totalAmount = 0;
    
    if (cart.length === 0) {
        cartItemsContainer.innerHTML = '<p class="empty-cart">Empty Cart</p>';
    } else {
        cart.forEach((item, index) => {
            const itemTotal = parseFloat(item.prix) * item.quantity;
            totalAmount += itemTotal;
            
            const cartItemElement = document.createElement('div');
            cartItemElement.className = 'cart-item';
            cartItemElement.innerHTML = `
                <div class="cart-item-quantity">${item.quantity}x</div>
                <div class="cart-item-name">${item.Nom}</div>
                <div class="cart-item-price">${itemTotal.toFixed(2)} CHF</div>
                <button class="remove-item-btn" data-index="${index}">×</button>
            `;
            
            cartItemsContainer.appendChild(cartItemElement);
        });
        
        // Ajouter des écouteurs d'événements pour les boutons de suppression
        document.querySelectorAll('.remove-item-btn').forEach(button => {
            button.addEventListener('click', function() {
                const index = parseInt(this.getAttribute('data-index'));
                removeCartItem(index);
            });
        });
    }
    
    // Mettre à jour le montant total
    document.getElementById('cart-total-amount').textContent = totalAmount.toFixed(2);
}

// Fonction pour supprimer un article du panier
function removeCartItem(index) {
    let cart = JSON.parse(localStorage.getItem('cart')) || [];
    
    cart.splice(index, 1);
    localStorage.setItem('cart', JSON.stringify(cart));
    
    displayCart();
    updateCartCount();
    
    // Mettre à jour le badge du panier dans le header
    if (typeof updateCartUI === 'function') {
        updateCartUI();
    }
}

// Fonction de recherche de produits
function searchProducts(query, products) {
    if (!query || query.trim() === '') {
        return products; // Retourne tous les produits si la recherche est vide
    }
    
    query = query.toLowerCase().trim();
    
    return products.filter(product => {
        // Vérifier si le produit a un nom valide
        if (!product.Nom) return false;
        
        const productName = product.Nom.toLowerCase();
        const productCategory = (product.categorie || '').toLowerCase();
        
        // Recherche dans le nom du produit et la catégorie
        return productName.includes(query) || productCategory.includes(query);
    });
}

// Fonction pour créer et ajouter le bouton flottant
function createFloatingButton() {
    // Vérifier si le bouton existe déjà
    if (document.getElementById('floatingAddToCartBtn')) return;
    
    // Créer le bouton flottant
    const floatingBtn = document.createElement('div');
    floatingBtn.id = 'floatingAddToCartBtn';
    floatingBtn.className = 'floating-add-to-cart-btn';
    floatingBtn.innerHTML = `
        <span id="floatingButtonCounter" class="floating-button-counter">0</span>
        <i class="fas fa-shopping-cart"></i>
        Add to Cart
    `;
    
    // Ajouter l'événement de clic
    floatingBtn.addEventListener('click', addAllSelectedToCart);
    
    // Ajouter le bouton au body
    document.body.appendChild(floatingBtn);
    
    // Ajouter le style pour le bouton flottant si ce n'est pas déjà fait dans le CSS
    if (!document.getElementById('floating-button-style')) {
        const style = document.createElement('style');
        style.id = 'floating-button-style';
        style.innerHTML = `
            .floating-add-to-cart-btn {
                position: fixed;
                bottom: 20px;
                right: 20px;
                background-color: #4CAF50;
                color: white;
                padding: 12px 20px;
                border-radius: 50px;
                box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
                cursor: pointer;
                z-index: 1000;
                display: flex;
                align-items: center;
                font-weight: bold;
                transition: all 0.3s ease;
            }
            
            .floating-add-to-cart-btn:hover {
                background-color: #45a049;
                transform: translateY(-2px);
                box-shadow: 0 6px 12px rgba(0, 0, 0, 0.3);
            }
            
            .floating-add-to-cart-btn i {
                margin-right: 8px;
            }
            
            .floating-button-counter {
                position: absolute;
                top: -8px;
                left: -8px;
                background-color: #ff6b6b;
                color: white;
                width: 24px;
                height: 24px;
                border-radius: 50%;
                display: none;
                align-items: center;
                justify-content: center;
                font-size: 12px;
                font-weight: bold;
            }
            
            /* Style pour les contrôles de quantité */
            .quantity-container {
                display: flex;
                align-items: center;
                justify-content: center;
                margin-bottom: 10px;
            }
            
            .quantity-btn {
                width: 30px;
                height: 30px;
                background-color: #f0f0f0;
                border: 1px solid #ddd;
                border-radius: 4px;
                font-size: 16px;
                display: flex;
                align-items: center;
                justify-content: center;
                cursor: pointer;
            }
            
            .quantity-input {
                width: 40px;
                height: 30px;
                text-align: center;
                margin: 0 5px;
                border: 1px solid #ddd;
                border-radius: 4px;
            }
            
            /* Style pour les éléments du panier */
            .cart-item {
                display: grid;
                grid-template-columns: 80px 1fr 100px 30px;
                gap: 16px;
                align-items: center;
                padding: 10px 0;
                border-bottom: 1px solid #eee;
            }
            
            .cart-item-quantity {
                text-align: left;
                font-weight: bold;
            }
            
            .cart-item-name {
                padding-left: 32px;
                text-align: left;
            }
            
            .cart-item-price {
                text-align: right;
                font-weight: bold;
            }
            
            .remove-item-btn {
                background: none;
                border: none;
                color: #ff6b6b;
                font-size: 18px;
                cursor: pointer;
                display: flex;
                align-items: center;
                justify-content: center;
            }
        `;
        document.head.appendChild(style);
    }
}

// Document ready
document.addEventListener('DOMContentLoaded', function() {
    // Variable pour stocker tous les produits
    let allProducts = [];
    
    // Créer le bouton flottant "Ajouter au panier"
    createFloatingButton();
    
    // Fonction pour effectuer la recherche
    function performSearch() {
        const searchQuery = document.getElementById('searchInput').value;
    
        // Si la recherche est vide, ne rien faire
        if (!searchQuery || searchQuery.trim() === '') {
            return;
        }
    
        // Si nous n'avons pas encore chargé les produits, faisons-le maintenant
        if (allProducts.length === 0) {
            fetchProducts().then(products => {
                allProducts = products.filter(p => p.Nom && p.Nom.trim() !== "");
                // Rechercher à travers TOUTES les catégories
                const filteredProducts = searchProducts(searchQuery, allProducts);
                displayProducts(filteredProducts);
                
                // Mettre à jour la sélection de catégorie
                document.getElementById('categoryFilter').value = "all";
                
                // Mettre à jour les éléments de catégorie dans le menu
                const categoryItems = document.querySelectorAll('.category-item');
                categoryItems.forEach(item => {
                    item.classList.remove('active');
                    if (item.getAttribute('data-category') === 'all') {
                        item.classList.add('active');
                    }
                });
            });
        } else {
            // Rechercher à travers TOUTES les catégories
            const filteredProducts = searchProducts(searchQuery, allProducts);
            displayProducts(filteredProducts);
            
            // Mettre à jour la sélection de catégorie
            document.getElementById('categoryFilter').value = "all";
            
            // Mettre à jour les éléments de catégorie dans le menu
            const categoryItems = document.querySelectorAll('.category-item');
            categoryItems.forEach(item => {
                item.classList.remove('active');
                if (item.getAttribute('data-category') === 'all') {
                    item.classList.add('active');
                }
            });
        }
    }
    
    // Écouteur d'événement pour la touche Entrée dans le champ de recherche
    const searchInput = document.getElementById('searchInput');
    if (searchInput) {
        searchInput.addEventListener('keyup', function(event) {
            if (event.key === 'Enter') {
                performSearch();
            }
        });
    }
    
    // Écouteur d'événement pour le bouton de recherche
    const searchButton = document.getElementById('searchButton');
    if (searchButton) {
        searchButton.addEventListener('click', performSearch);
    }
    
    // Filtre par catégorie (pour le select caché)
    const categoryFilter = document.getElementById('categoryFilter');
    if (categoryFilter) {
        categoryFilter.addEventListener('change', async function() {
            const selectedCategory = this.value;
            
            // Obtenir la valeur actuelle de la recherche
            const searchQuery = document.getElementById('searchInput')?.value || '';
            
            // Si une recherche est en cours, filtrer d'abord par la recherche
            if (searchQuery && searchQuery.trim() !== '') {
                // Si nous n'avons pas encore chargé les produits, faisons-le maintenant
                if (allProducts.length === 0) {
                    allProducts = await fetchProducts();
                    allProducts = allProducts.filter(p => p.Nom && p.Nom.trim() !== "");
                }
                
                const searchFilteredProducts = searchProducts(searchQuery, allProducts);
                
                // Puis appliquer le filtre de catégorie
                if (selectedCategory === "all") {
                    displayProducts(searchFilteredProducts);
                } else {
                    const finalFilteredProducts = searchFilteredProducts.filter(p => p.categorie === selectedCategory);
                    displayProducts(finalFilteredProducts);
                }
            } else {
                // Sinon, simplement filtrer par catégorie comme avant
                if (allProducts.length === 0) {
                    allProducts = await fetchProducts();
                    allProducts = allProducts.filter(p => p.Nom && p.Nom.trim() !== "");
                }
                displayProducts(allProducts, selectedCategory);
            }
        });
    }
    
    // Afficher le panier quand on clique sur l'icône du panier
    const cartToggle = document.getElementById('cartToggle');
    if (cartToggle) {
        cartToggle.addEventListener('click', function() {
            const cartModal = document.getElementById('cart-modal');
            if (cartModal) {
                displayCart(); // Mettre à jour le contenu du panier
                cartModal.style.display = 'block';
            }
        });
    }
    
    // Fermer la modale du panier
    const closeModal = document.querySelector('.close-modal');
    if (closeModal) {
        closeModal.addEventListener('click', function() {
            const cartModal = document.getElementById('cart-modal');
            if (cartModal) {
                cartModal.style.display = 'none';
            }
        });
    }
    
    // Clic en dehors de la modale pour la fermer
    window.addEventListener('click', function(event) {
        const cartModal = document.getElementById('cart-modal');
        if (cartModal && event.target === cartModal) {
            cartModal.style.display = 'none';
        }
    });
    
    // Checkout button
    const checkoutBtn = document.getElementById('checkout-btn');
    if (checkoutBtn) {
        checkoutBtn.addEventListener('click', function() {
            const cart = JSON.parse(localStorage.getItem('cart')) || [];
            
            if (cart.length === 0) {
                showNotification('Empty Cart', 'error');
                return;
            }
            
            // Envoyer la commande au serveur
            fetch('/api/save-order', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ items: cart })
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    showNotification('Order placed successfully !', 'success');
                    // Vider le panier après la commande
                    localStorage.removeItem('cart');
                    updateCartCount();
                    // Mettre à jour le badge du panier dans le header
                    if (typeof updateCartUI === 'function') {
                        updateCartUI();
                    }
                    // Fermer la modale du panier
                    const cartModal = document.getElementById('cart-modal');
                    if (cartModal) {
                        cartModal.style.display = 'none';
                    }
                }
            })
            .catch(error => {
                console.error('Erreur:', error);
                showNotification('Erreur lors de la commande', 'error');
            });
        });
    }
    
    // Chargement initial des produits
    (async () => {
        allProducts = await fetchProducts();
        // Filtrer les produits sans nom valide pour éviter les "Produit sans nom"
        allProducts = allProducts.filter(p => p.Nom && p.Nom.trim() !== "");
        displayProducts(allProducts);
        updateCartCount();
    })();
});

// Add this code to your script.js file or create a new file and include it in your HTML: zoom image catalogue 

document.addEventListener('DOMContentLoaded', function() {
    // Create the image preview modal
    const modal = document.createElement('div');
    modal.id = 'image-preview-modal';
    modal.className = 'image-preview-modal';
    modal.innerHTML = `
        <div class="image-preview-content">
            <span class="close-preview">&times;</span>
            <img class="preview-image" src="" alt="Product preview">
        </div>
    `;
    document.body.appendChild(modal);

    // Get the modal elements
    const previewImage = modal.querySelector('.preview-image');
    const closeButton = modal.querySelector('.close-preview');

    // Add click event listener to all product images
    function setupImagePreviews() {
        const productImages = document.querySelectorAll('.product-img');
        
        productImages.forEach(img => {
            // Only add the click event if it doesn't already have one
            if (!img.hasAttribute('data-preview-enabled')) {
                img.style.cursor = 'zoom-in'; // Change cursor to indicate clickable
                
                img.addEventListener('click', function(event) {
                    event.preventDefault(); // Prevent any default behavior
                    
                    // Get high resolution image URL (could be the same as the thumbnail)
                    const highResUrl = this.getAttribute('data-high-res') || this.src;
                    
                    // Set the preview image source
                    previewImage.src = highResUrl;
                    
                    // Show the modal
                    modal.style.display = 'flex';
                    
                    // Add animation class
                    modal.classList.add('show-preview');
                });
                
                // Mark this image as having the preview enabled
                img.setAttribute('data-preview-enabled', 'true');
            }
        });
    }

    // Close the modal when clicking the close button
    closeButton.addEventListener('click', function() {
        modal.classList.remove('show-preview');
        setTimeout(() => {
            modal.style.display = 'none';
        }, 300); // Wait for animation to complete
    });

    // Close the modal when clicking outside the image
    modal.addEventListener('click', function(event) {
        if (event.target === modal) {
            modal.classList.remove('show-preview');
            setTimeout(() => {
                modal.style.display = 'none';
            }, 300); // Wait for animation to complete
        }
    });

    // Set up image previews initially
    setupImagePreviews();
    
    // Re-run setup when new products might be loaded (e.g., after filtering)
    document.addEventListener('productsLoaded', setupImagePreviews);
    
    // If you're using category filters or search, you might need to call setupImagePreviews() 
    // after those operations complete as well. For example:
    const categoryFilter = document.getElementById('categoryFilter');
    if (categoryFilter) {
        categoryFilter.addEventListener('change', function() {
            // Wait a moment for the DOM to update with new products
            setTimeout(setupImagePreviews, 300);
        });
    }
    
    // For search functionality
    const searchButton = document.getElementById('searchButton');
    if (searchButton) {
        searchButton.addEventListener('click', function() {
            // Wait a moment for the DOM to update with new products
            setTimeout(setupImagePreviews, 300);
        });
    }
    
    // Modify the displayProducts function to trigger an event when products are loaded
    // This assumes you have access to modify the original displayProducts function
    const originalDisplayProducts = window.displayProducts;
    if (typeof originalDisplayProducts === 'function') {
        window.displayProducts = function(products, category) {
            originalDisplayProducts(products, category);
            
            // Dispatch an event to signal that products have been loaded
            document.dispatchEvent(new CustomEvent('productsLoaded'));
        };
    }
});


