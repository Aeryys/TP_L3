
$(document).ready(function() {
    


        
    $("button:eq(0)").click(function(){
        if ($("input:eq(0)").prop("checked") == true){
            $("img").fadeIn(1000); //Apparait
        }

        else if ($("input:eq(1)").prop("checked") == true){
            $("img").slideDown();

        }
    });


    $("button:eq(1)").click(function(){
        if ($("input:eq(0)").prop("checked") == true){
            $("img").fadeOut(); //Disparait 
        }
        else if ($("input:eq(1)").prop("checked") == true){        
            $("img").slideUp();
        }
    });



    $("input:eq(0)").click(function(){
        $("img").slideDown();
        $("button:eq(0)").text("Apparaître");
        $("button:eq(1)").text("Disparaitre");

    });

    $("input:eq(1)").click(function(){
        $("img").fadeIn(1000);
        $("button:eq(0)").text("Haut");
        $("button:eq(1)").text("Bas");
    });



});


