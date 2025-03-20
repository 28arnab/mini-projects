const toggle = document.getElementById('toggle');

    toggle.addEventListener('change', function() {
        document.body.classList.toggle("dark-mode", this.checked);
    });