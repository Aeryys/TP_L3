$(document).ready(function() {

    $("#ag").click(function() {
        $("p:eq(0)").addClass("grand");
    });

    $("#red").click(function() {
        $("p:eq(0)").removeClass("grand");
    });

    $("button:eq(2)").click(function() {

        $("p:eq(0)").text($("input").val());
        $("input").val("");
    });
});