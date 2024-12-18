window.onload = async function () {
  const response = await fetch("degustware.com.br/api")
  const products = await response.json()

  const productList = document.getElementById("product-list")
  products.forEach(product => {
    const li = document.createElement("li")
    li.textContent = `${product.name} - R$${product.price}`
    productList.appendChild(li)
  })
}
