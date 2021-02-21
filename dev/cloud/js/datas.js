
// Realise un GET sur datas.php et recupere le Json contenant les infos de la dernière position. 
// Puis affiche les points de position sur la carte 

function get_data_device(/*location_id*/) {

  console.log("get_data_device()");

  var alt;
  var lat;
  var lng;

  var data_obj;

  $.ajax({
    url: '../php/datas.php',
    type : 'GET',
    dataType : 'json',
    async: false,
    success : function(data){
      console.log("AJAX GET SUCCESS");

      console.log("data receive from data.php (CHANGE) :");
      console.log(data);

      data_obj = data;

    },
    error : function(resultat, statut, erreur){
      console.log("AJAX GET ERROR");
    },
  });

  //return [alt, lat, lng];
  return data_obj;
}