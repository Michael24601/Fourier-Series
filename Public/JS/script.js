
// Loads the image and the text
$(document).ready( () => {
    $('#form').on('submit', (e) => {
        let formData = new FormData($("#form")[0]);
        console.log(formData);
        e.preventDefault();
        $.ajax({
            url : 'postImage',
            type: "POST",
            data: formData,
            processData: false,
            contentType: false,
            success: (data) => {

                // uploading an image
                console.log(data);
                let image = $('#image');
                image.attr("src", data["SVG path"]);

                //adding the text
                $("#width").append(`<p>${data["Width"]}</p>`);
                $("#height").append(`<p>${data["Height"]}</p>`);
                $("#svgpath").append(`<p>${data["SVG"]}</p>`);
                $("#pathassent").append(`<p>${data["Path as sent to addon"]}</p>`);
                $("#beziercurves").append(`<p>${data["Bezier Curves"]}</p>`);
                $("#vectors").append(`<p>${data["Vectors"]}</p>`);
                $("#fourierseries").append(`<p id="output">${data["Fourier Series"]}</p>`);
            },
            error: function (jXHR, textStatus, errorThrown) {
                alert(errorThrown);
            }
        });
    });
});

//Displays images once it has been uploaded for inspection
let loadFile = (event) => {
    $("#form").submit();
};
