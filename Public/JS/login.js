const forms = document.querySelector(".forms"),
    pwShowHide = document.querySelectorAll(".eye-icon"),
    links = document.querySelectorAll(".link");


pwShowHide.forEach(eyeIcon => {
    eyeIcon.addEventListener("click", () => {
        let pwFields = eyeIcon.parentElement.querySelectorAll(".password");

        pwFields.forEach(password => {
            if (password.type === "password") {
                password.type = "text";
                eyeIcon.classList.replace("bx-hide", "bx-show");
                return;
            }
            password.type = "password";
            eyeIcon.classList.replace("bx-show", "bx-hide");
        })

    })
});

$('#login-form').on('submit', (e) => {
    let formData = {
        username: $("#login-username").val(),
        password: $("#login-password").val()
    }
    e.preventDefault();
    $.ajax({
        url : 'login',
        type: "POST",
        data: formData,
        success: (data) => {
            
        },
        error: function (request, status, error) {
            if(request.status === 401){
                $("#login-password").val('');
                $("#login-error-message").text(request.responseText);
                $("#login-password-field").addClass('error');
            }
        }
    });
});