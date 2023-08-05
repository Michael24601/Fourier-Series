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

$('#signup-form').on('submit', (e) => {

    let password = $("#signup-password").val(),
        confirmPassword = $("#signup-confirm-password").val();

    if(password !== confirmPassword){
        $("#signup-error-message").text('Passwords do not match');
        $("#signup-password-field").addClass('error');
        $("#signup-confirm-password-field").addClass('error');
        return;
    }

    let formData = {
        username: $("#signup-username").val(),
        password: password
    }
    e.preventDefault();
    $.ajax({
        url : 'signup',
        type: "POST",
        data: formData,
        success: (data) => {
            console.log(data);
        },
        error: function (request, status, error) {
            if(request.status === 409){
                $("#signup-error-message").text(request.responseText);
                $("#signup-username-field").addClass('error');
            }
        }
    });
});

