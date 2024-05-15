//importation des modules necessaire pour gérer les requêtes GraphQL et mettre en place le schéma GraphQL.
const express = require('express');
const { graphqlHTTP } = require('express-graphql');
const { makeExecutableSchema } = require('graphql-tools');
const cors = require('cors');

// Schéma GraphQL
const typeDefs = `
  type Query {
    getLEDState: Boolean
    getTemperature: Float
    getHumidity: Float
    getAlertState:Boolean
  }
  type Mutation {
    setLEDState(state: Boolean): Boolean
    setTemperature(temp: Float): Float
    setHumidity(hum: Float): Float

    triggerAlert: Boolean
  }
`;

let ledState = false; // État LED par défaut
let temperature = 0.0; //etat température par défaut
let humidity = 0.0; //etat humidity par défaut

//implémentation des resolvers qui 
//déterminent comment répondre à chaque requête ou mutation GraphQL.
const resolvers = {
  Mutation: {
    setHumidity: (_, { hum }) => {
      humidity = hum;
      console.log(`Humidity set to: ${humidity}`);
      return humidity;
    },
    setTemperature: (_, { temp }) => {
      if (typeof temp === 'number') {
        temperature = temp;
        console.log(`Temperature set to: ${temperature}`);
        return temperature;
      } else {
        throw new Error("Temperature 'temp' argument must be a number.");
      }
    },
    setLEDState: (_, { state }) => {
      ledState = state;
      console.log(`LED state set to: ${ledState}`);
      return ledState;
    },
    triggerAlert: (_, {alert}) => {
      isAlertTriggered = alert;
      // Logique pour gérer l'alerte, par exemple : envoyer une notification, enregistrer dans une base de données, etc.
      return true;
    }
  },
  Query: {
    getLEDState: () => {
      console.log(`Fetching LED state: ${ledState}`);
      return ledState;
    },
    getTemperature: () => {
      console.log(`Fetching temperature: ${temperature}`);
      return temperature;
    },
    getHumidity: () => {
      console.log(`Fetching humidity: ${humidity}`);
      return humidity;
    }
  }
};

//creation shéma éxécutable
const schema = makeExecutableSchema({
  typeDefs,
  resolvers,
});

// Créer une application express
const app = express();
// Middleware to enable CORS:  utilisé pour autoriser les requêtes de différentes origines.
app.use(cors());
// Définir le point d'accès GraphQL avec express-graphql
app.use('/graphql', graphqlHTTP({
  schema: schema,
  graphiql: true, // Activer l'interface GraphiQL pour les tests
}));



  
//configuration point d'accés pour page web
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/wrb.html');
  });

//lancement serveur express 
app.listen(4000, () => console.log('Serveur GraphQL Express en cours d exécution sur localhost:4000/graphql'));

//lancement serveur express pour la page web
app.listen(5500, () => {
    console.log('Web interface available at http://192.168.137.63:5500/projetweb/wrb.html');
  });