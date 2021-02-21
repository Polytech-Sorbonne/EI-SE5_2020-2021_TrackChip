let map, window_current_pos, window_tracker_pos;

var curr_pos, tracker_pos;

var current_alt         = 0;
var current_tracket_alt = 0;

var span_time           = document.getElementById("time");
var span_dist           = document.getElementById("dist");
var span_abs_diff_alt   = document.getElementById("abs_diff_alt");
var span_arrow_alt      = document.getElementById("arrow");

let markers             = [];
let pos_marker          = [];

var nb_position_display = 10;

function initMap() {
  
  console.log("initMap()");

  const directionsService   = new google.maps.DirectionsService();
  const directionsRenderer  = new google.maps.DirectionsRenderer();
  const geocoder            = new google.maps.Geocoder();
  const dist_service        = new google.maps.DistanceMatrixService();

  // Default position : center of Paris
  map = new google.maps.Map(document.getElementById("map"), {
    center: { lat: 48.858725, lng: 2.341706 },
    zoom: 12,
  });

  directionsRenderer.setMap(map);

  // Create elevation service for current position
  const current_elevator = new google.maps.ElevationService();

  // Create info window for current position
  window_current_pos = new google.maps.InfoWindow();

  // Create info window for tracker position
  window_tracker_pos = new google.maps.InfoWindow();

  // button to get current position
  const button_current_pos  = document.createElement("button");

  // button to get tracket position
  const button_tracker_pos  = document.createElement("button");

  // button to get itinerary between current and tracker pos
  const button_itineraty    = document.createElement("button");

  // Customize buttons
  button_current_pos.textContent = "View Current Location";
  button_current_pos.classList.add("custom-map-control-button");

  button_tracker_pos.textContent = "View Tracker Location";
  button_tracker_pos.classList.add("custom-map-control-button");

  button_itineraty.textContent = "Get Route";
  button_itineraty.classList.add("custom-map-control-button");
  
  // Add buttons to map
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(
    button_current_pos
  );
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(
    button_tracker_pos
  );
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(
    button_itineraty
  );

  button_current_pos.addEventListener("click", () => {
    console.log("Click on current pos button");
    // Try HTML5 geolocation.
    if (navigator.geolocation) {
      navigator.geolocation.getCurrentPosition(
        (position) => {
          
          curr_pos = { lat: position.coords.latitude, lng: position.coords.longitude };

          getElevation(curr_pos, current_elevator);

          window_current_pos.setPosition(curr_pos);
          // window_current_pos.setContent("Current Location found.");
          geocodeLatLng(geocoder, map, window_current_pos, curr_pos, 0);

          window_current_pos.open(map);
          
          map.setCenter(curr_pos);
          map.setZoom(11);

        }, () => { handleLocationError(true, window_current_pos, map.getCenter()); }
      );
    } 
    else {
      // Browser doesn't support Geolocation
      handleLocationError(false, window_current_pos, map.getCenter());
    }
  });

  button_tracker_pos.addEventListener("click", () => {
    console.log("Click on tracker pos button");

    // remove all markers
    clearMarkers();
    markers     = [];
    pos_marker  = [];

    // Rely all old tracker's positions
    const flightPlanCoordinates = [];

    // call fonction which GET datas.php
    let data_array;
    data_array = get_data_device();

    console.log(data_array);

    nb_position_display = data_array['length'];
    console.log('nb_position_display : ');
    console.log(nb_position_display);

    for (var i = 0; i < nb_position_display; i++) {

      console.log('i : ');
      console.log(i);
      console.log(data_array[i]);

      element = data_array[i];

      console.log(element['altitude']);
      console.log(element['latitude']);
      console.log(element['longitude']);

      current_tracket_alt = element['altitude'];

      pos_marker.push({ lat: element['latitude'], lng: element['longitude'] });


      if (i != nb_position_display - 1){
        // add circle marker on each old tracker's position
        console.log("circle marker");

        markers.push(new google.maps.Marker({
          position: pos_marker[i],
          icon: {
            path: google.maps.SymbolPath.CIRCLE,
            scale: 5,
          },
          map: map,
        }));
      }
      else {
        // add clasic marker on current tracker position
        console.log("classic marker");

        markers.push(new google.maps.Marker({
          position: pos_marker[i],
          map: map,
        }));
      }

    flightPlanCoordinates.push(pos_marker[i]);

    }

    tracker_marker = markers[nb_position_display - 1];
    
    const flightPath = new google.maps.Polyline({
      path: flightPlanCoordinates,
      geodesic: true,
      strokeColor: "#000000",
      strokeOpacity: 1.0,
      strokeWeight: 2,
    });
    flightPath.setMap(map);

    tracker_pos = pos_marker[nb_position_display - 1];

    window_tracker_pos.setPosition(pos_marker[nb_position_display - 1]);
    // window_tracker_pos.setContent("Tracker Location found.");
    geocodeLatLng(geocoder, map, window_tracker_pos, pos_marker[nb_position_display - 1], 1);

    // window_tracker_pos.open(map);
    tracker_marker.addListener("click", () => {
      window_tracker_pos.open(map, tracker_marker);
    });
    
    map.setCenter(tracker_pos);
    map.setZoom(16);

    handleLocationError(true, window_tracker_pos, map.getCenter());
  });

  button_itineraty.addEventListener("click", () => {
    console.log("Click on route button");

    dist_service.getDistanceMatrix(
    {
      origins: [curr_pos],
      destinations: [tracker_pos],
      travelMode: google.maps.TravelMode.DRIVING,
      unitSystem: google.maps.UnitSystem.METRIC,
      avoidHighways: false,
      avoidTolls: false,
    },
    (response, status) => {
      if (status !== "OK") {
        alert("Error was: " + status);
      } 
      else {

        var results = response.rows[0].elements;
        var element = results[0];
        var distance = element.distance.text;
        var duration = element.duration.text;

        console.log('distance :');
        console.log(distance); 
        span_dist.innerHTML = distance;

        console.log('duration :');
        console.log(duration);
        span_time.innerHTML = duration;

      }
    });

    // do some tests on position available !
    calculateAndDisplayRoute(directionsService, directionsRenderer);
  });
}

function clearMarkers() {
  for (let i = 0; i < markers.length; i++) {
    markers[i].setMap(null);
  }
}

function handleLocationError(browserHasGeolocation, window_info, pos) {
  window_info.setPosition(pos);
  
  if (!browserHasGeolocation){
    window_info.setContent("Error: The Geolocation service failed.");
  }
}

function getElevation(location, elevator) {

  console.log("getElevation()");

  // Initiate the location request
  elevator.getElevationForLocations(
    {
      locations: [location],
    },
    (results, status) => {
      if (status === "OK") {
        
        // Retrieve the first result
        if (results[0]) 
        {
          current_alt     = results[0].elevation;

          var signed_diff = current_alt - current_tracket_alt;
          var abs_diff    = Math.abs(current_alt - current_tracket_alt);
  
          // cast to integer
          abs_diff = parseInt(abs_diff, 10);

          span_abs_diff_alt.innerHTML = abs_diff;

          if (signed_diff > 2) 
          {
            span_arrow_alt.innerHTML = '&darr;';
          }
          else if (signed_diff < 2) 
          {
            span_arrow_alt.innerHTML = '&uarr;';
          }
          else{
            span_arrow_alt.innerHTML = '&harr;';
          }
        } 
        else {
          console.log("No results found");
        }
      } 
      else {
        console.log("Elevation service failed due to: " + status)
      }
    }
  );
}

function geocodeLatLng(geocoder, map, infowindow, latlng, pos) {

  console.log("geocodeLatLng()");

  geocoder.geocode({ location: latlng }, (results, status) => {
    if (status === "OK") 
    {
      if (results[0]) 
      {
        // current pos
        if (pos == 0) 
        {
          infowindow.setContent("Current Location : \n" + results[0].formatted_address);
        }
        // tracker pos`
        else{
          infowindow.setContent("Tracker Location : \n" + results[0].formatted_address);
        }
        
      } 
      else {
        window.alert("No results found");
      }
    } 
    else {
      window.alert("Geocoder failed due to: " + status);
    }
  });
}

function calculateAndDisplayRoute(directionsService, directionsRenderer) {
  directionsService.route(
    {
      origin: curr_pos,
      destination: tracker_pos,
      travelMode: google.maps.TravelMode.DRIVING,
    },
    (response, status) => {
      if (status === "OK") {
        directionsRenderer.setDirections(response);
      } else {
        window.alert("Directions request failed due to " + status);
      }
    }
  );
}