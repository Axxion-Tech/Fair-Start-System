const toggleDropdown = (element) => {
    if (element.classList.contains("collapsed")) {
        let content = element.querySelector(".hidden")
        element.classList.remove("collapsed")
        element.classList.add("expanded")
        content.classList.remove("hidden")
        content.classList.add("show")
    } else {
        let content = element.querySelector(".show")
        element.classList.remove("expanded")
        element.classList.add("collapsed")
        content.classList.remove("show")
        content.classList.add("hidden")
    }
}

let tutorials = document.querySelectorAll(".tutorial")
console.log(tutorials)
tutorials.forEach(tutorial => tutorial.addEventListener('click', () => toggleDropdown(tutorial)))