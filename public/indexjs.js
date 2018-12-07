var config = {
    apiKey: "AIzaSyBn5KIozbTgwD3VUSuulDNcy554BoMBLHY",
    authDomain: "dooropener-699b5.firebaseapp.com",
    databaseURL: "https://dooropener-699b5.firebaseio.com"
};
firebase.initializeApp(config);

// Get a reference to the database service
var database = firebase.database();


function updateData() {
    firebase.database().set({
        Test: 9,
    });
}