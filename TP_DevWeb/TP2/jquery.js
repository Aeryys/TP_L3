$(document).ready(function() {
    $("body").append("<h1>Hello World avec jQuery</h1>");

    let compteur = 1;

    $("#ajouter").click(function() {
        $("#listeTaches").append('<li>Tâche ' + compteur + '</li>');
    compteur = compteur + 1;
    });
    
});
