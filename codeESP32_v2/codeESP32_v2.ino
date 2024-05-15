

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

/*Définition des paramètres de connexion Wi-Fi et de l'URL du serveur GraphQL
const char* ssid = "Redmi Note 10 Pro";
const char* password = "Ranim123*";*/
const char* ssid = "Mi Note 10 Lite";
const char* password = "7db531f5ac8e";

const char* serverUrl = "http://192.168.137.63:4000/graphql";
const int sensorPin = 4; // Pin de données du capteur DH11
const int ledPin = 2;     // Pin de la LED

const int DHTType = DHT11; // Type de capteur DH11
DHT dht(sensorPin, DHTType);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);//cofiguration cnxion wifi
 
  pinMode(ledPin, OUTPUT); // Définir le pin de la LED en mode sortie
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
  Serial.println("Connecté au WiFi");

  dht.begin();
}




void triggerAlert() {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Requête GraphQL pour la température
    String alertQuery = "{\"query\":\"mutation { triggerAlert(alert:true)}\"}";
    Serial.print(alertQuery);
    int httpResponseCode = http.POST(alertQuery);

  if (httpResponseCode == 200) {
    Serial.println("Alerte déclenchée avec succès !");
  } else {
    Serial.print("Erreur lors du déclenchement de l'alerte. Code de réponse : ");
    Serial.println(httpResponseCode);
  }

  http.end();
}







void loop() {
  delay(5000); // Attendre quelques secondes entre chaque lecture de capteur

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur");
    return;
  }

  Serial.print("Humidité: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.println("°C");

  //Envoyer les données de température et d'humidité au serveur GraphQL
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Requête GraphQL pour la température
    String temperatureQuery = "{\"query\":\"mutation { setTemperature(temp: " + String(temperature) + ") }\"}";
    Serial.print(temperatureQuery);
    int temperatureResponse = http.POST(temperatureQuery);

    // Requête GraphQL pour l'humidité
    String humidityQuery = "{\"query\":\"mutation { setHumidity(hum: " + String(humidity) + ") }\"}";
    Serial.print(humidityQuery);
    int humidityResponse = http.POST(humidityQuery);

// Vérifier les conditions d'alerte
  if (temperature > 20 || humidity > 50) {
    // Déclencher l'alerte et allumer la LED
    triggerAlert();
    digitalWrite(ledPin, HIGH); // Allumer la LED
  } else {
    digitalWrite(ledPin, LOW); // Éteindre la LED si les conditions d'alerte ne sont pas rencontrées
  }









    http.end();
  }








  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    // Declare ledState within the correct scope
    boolean ledState;
    // Requête GraphQL pour l'état de la LED
    String ledQuery = "{\"query\":\"query { getLEDState }\"}";
    int ledResponse = http.POST(ledQuery);

    if (ledResponse > 0) {
      String response = http.getString();
      Serial.println("Réponse du serveur GraphQL : " + response);

      // Analyse de la réponse pour obtenir l'état de la LED
      if (response.indexOf("true") >= 0) {
        ledState = true;
      } else {
        ledState = false;
      }
    } else {
      Serial.println("Erreur lors de la requête GraphQL pour l'état de la LED");
    }

    http.end();

      // Contrôle de la LED
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  }
  

}
