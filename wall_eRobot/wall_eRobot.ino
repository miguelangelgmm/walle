#include <WiFi.h>
#include <WebServer.h>
#include <DFRobotDFPlayerMini.h>
#include <Adafruit_PWMServoDriver.h>

const char* ssid = "MOVISTAR_94C2";
const char* password = "4100ECED7E869F229139";

// Crear un objeto WebServer en el puerto 80
WebServer server(80);

//interacción con servos 
Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

int pos0 = 102;
int pos180 = 512;

int posCabeza = 90;
int posCuello = 70;
int posBrazoD = 70;
int posBrazoI = 0;

// Definir pines para el DFPlayer
const int dfPlayerRX = 4;
const int dfPlayerTX = 5;

//define los pines de los motores

const int Minp1 = 14;
const int Minp2 = 27;
const int Minp3 = 26;
const int Minp4 = 25;

//velocidad de los motores
const int MpinV1 = 12;
const int MpinV2 = 33;


// Crear objeto DFPlayer
DFRobotDFPlayerMini dfPlayer;

// Reproducir sonido usando DFPlayer
void playSound(int track) {
  dfPlayer.play(track);
  Serial.printf("Reproduciendo sonido %d\n", track);
}



// Función para manejar la página principal
void handleRoot() {
  // Página HTML con estilo Wall-E
  String html = R"rawliteral(
    <html>
      <head>
        <meta charset="UTF-8">
        <title>Control de Robot Wall-E</title>
        <style>
          body {
            font-family: 'Arial', sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 0;
            background-image: url('https://hips.hearstapps.com/es.h-cdn.co/fotoes/images/peliculas/wall-e/galeria/3139610-3-esl-ES/Wall-E.jpg');
            background-size: cover;
            background-position: center;
          }
          .container {
            max-width: 800px;
            margin: auto;
            padding: 20px;
            background: rgba(255, 255, 255, 0.8);
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.3);
          }
          h1 {
            color: #333;
            text-align: center;
          }
          .button-container,
          .dropdown-container,
          .volume-container {
            margin-bottom: 20px;
          }
          .dropdown-container label,
          .volume-container label {
            display: block;
            margin: 10px 0;
            font-size: 18px;
          }
          .dropdown-container select,
          .volume-container input {
            width: 100%;
            margin-top: 5px;
          }
          .button-container button {
            padding: 10px;
            font-size: 16px;
            background-color: #f9c74f;
            color: #333;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            margin: 5px;
          }
          .button-container button:hover {
            background-color: #f94144;
            color: white;
          }
          .instructions {
            margin-top: 20px;
            font-size: 16px;
            text-align: center;
            color: #333;
          }
        </style>
        <script>
          function sendAction(action) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/action?action=" + action, true);
            xhr.send();
          }

          function playSelectedSong() {
            var track = document.getElementById('song-select').value;
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/play?song=" + track, true);
            xhr.send();
          }

          function setVolume() {
            var volume = document.getElementById('volume-slider').value;
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/setVolume?volume=" + volume, true);
            xhr.send();
          }

          function setupButtons() {
            document.querySelectorAll('.action-button').forEach(function(button) {
              button.addEventListener('click', function() {
                var action = this.dataset.action;
                sendAction(action);
              });
            });
          }

          document.addEventListener('DOMContentLoaded', function() {
            setupButtons();
            document.getElementById('volume-slider').addEventListener('input', setVolume);
          });
        </script>
      </head>
      <body>
        <div class="container">
          <h1>Control de Robot Wall-E</h1>

          <div class="dropdown-container">
            <label for="song-select">Selecciona una canción:</label>
            <select id="song-select" onchange="playSelectedSong()">
              <option value="1">Canción 1</option>
              <option value="2">Canción 2</option>
              <option value="3">Canción 3</option>
              <option value="4">Canción 4</option>
              <option value="5">Canción 5</option>
              <option value="6">Canción 6</option>
              <option value="7">Canción 7</option>
              <option value="8">Canción 8</option>
              <option value="9">Canción 9</option>
              <option value="10">Canción 10</option>
              <option value="11">Canción 11</option>
              <option value="12">Canción 12</option>
              <option value="13">Canción 13</option>
              <option value="14">Canción 14</option>
              <option value="15">Canción 15</option>
              <option value="16">Canción 16</option>
              <option value="17">Canción 17</option>
              <option value="18">Canción 18</option>
              
              <option value="19">Canción 19</option>
              <option value="20">Canción 20</option>
              <option value="21">Canción 21</option>
              <option value="22">Canción 22</option>
              <option value="23">Canción 23</option>
              <option value="24">Canción 24</option>
              <option value="25">Canción 25</option>
              <option value="26">Canción 26</option>
              <option value="27">Canción 27</option>
              <option value="28">Canción 28</option>
              <option value="29">Canción 29</option>
              <option value="30">Canción 30</option>
              <option value="31">Canción 30</option>
            </select>
          </div>

          <div class="volume-container">
            <label for="volume-slider">Volumen:</label>
            <input type="range" id="volume-slider" min="0" max="30" value="15" />
          </div>

          <div class="button-container">
            <h3>Controles Rápidos</h3>
            <button class="action-button" data-action="greeting">Saludo</button>
            <button class="action-button" data-action="sayNo">Decir No</button>
            <button class="action-button" data-action="turnHeadRight">Girar Cabeza Derecha</button>
            <button class="action-button" data-action="turnHeadLeft">Girar Cabeza Izquierda</button>
            <button class="action-button" data-action="raiseNeck">Subir Cuello</button>
            <button class="action-button" data-action="lowerNeck">Bajar Cuello</button>
            <button class="action-button" data-action="setNeckMid">Establecer Cuello</button>
            <button class="action-button" data-action="raiseArms">Subir Brazos</button>
            <button class="action-button" data-action="lowerArms">Bajar Brazos</button>
            <button class="action-button" data-action="raiseRightArm">Subir Brazo Derecho</button>
            <button class="action-button" data-action="lowerRightArm">Bajar Brazo Derecho</button>
            <button class="action-button" data-action="raiseLeftArm">Subir Brazo Izquierdo</button>
            <button class="action-button" data-action="lowerLeftArm">Bajar Brazo Izquierdo</button>
            <button class="action-button" data-action="pauseMusic">Pausar canción</button>
            <button class="action-button" data-action="startMusic">Reanudar canción</button>
            <button class="action-button" data-action="randomMusic">canción aleatoria</button>
            
          </div>
          <div class="button-container">
          <h3>Controles de Movimiento</h3>
          <button class="action-button" data-action="moveForward">Mover Adelante</button>
          <button class="action-button" data-action="moveBackward">Marcha Atrás</button>
          <button class="action-button" data-action="turnRight">Girar Derecha</button>
          <button class="action-button" data-action="turnLeft">Girar Izquierda</button>
          <button class="action-button" data-action="moveForward2">Mover Adelante sin pausa</button>
          <button class="action-button" data-action="stopMotors">detener</button>
        </div>
          <div class="instructions">
            <p>Usa los botones para realizar acciones rápidas o ajusta el volumen.</p>
          </div>
        </div>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}



// Función para manejar el control del volumen
void handleSetVolume() {
  if (server.hasArg("volume")) {
    int volume = server.arg("volume").toInt();
    if (volume >= 0 && volume <= 30) {
      dfPlayer.volume(volume); // Ajusta el volumen del DFPlayer
      Serial.printf("Volumen ajustado a: %d\n", volume);
      server.send(200, "text/plain", "Volumen ajustado a: " + String(volume));
    } else {
      server.send(400, "text/plain", "Error: Volumen fuera de rango");
    }
  } else {
    server.send(400, "text/plain", "Error: No se recibió volumen");
  }
}

// Función para manejar la reproducción de canciones
void handlePlaySound() {
  if (server.hasArg("song")) {
    int track = server.arg("song").toInt();
    if (track >= 1 && track <= 50) {
      playSound(track);
      server.send(200, "text/plain", "Reproduciendo canción: " + String(track));
    } else {
      server.send(400, "text/plain", "Error: Canción fuera de rango");
    }
  } else {
    server.send(400, "text/plain", "Error: No se recibió canción");
  }
}

// Configurar el servidor
void setup() {
  Serial.begin(115200);

  // Configurar DFPlayer
  delay(100);
  Serial1.begin(9600, SERIAL_8N1, dfPlayerRX, dfPlayerTX);
  if (!dfPlayer.begin(Serial1)) {
    Serial.println("Error al inicializar DFPlayer");
    while (true);
  }
  dfPlayer.volume(15); // Configura el volumen inicial

  // Conectar a Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Definir rutas para el servidor
  server.on("/", handleRoot);
  server.on("/action", handleAction);
  server.on("/setVolume", handleSetVolume);
  server.on("/play", handlePlaySound);
server.on("/moveForward", []() {
  moveForward();
  server.send(200, "text/plain", "Moviendo hacia adelante");
});
server.on("/moveForward2", []() {
  moveForward2();
  server.send(200, "text/plain", "Moviendo hacia adelante");
});

server.on("/stopMotors", []() {
  stopMotors();
  server.send(200, "text/plain", "Moviendo hacia adelante");
});

server.on("/moveBackward", []() {
  moveBackward();
  server.send(200, "text/plain", "Marcha atrás");
});

server.on("/turnRight", []() {
  turnRight();
  server.send(200, "text/plain", "Girando a la derecha");
});

server.on("/turnLeft", []() {
  turnLeft();
  server.send(200, "text/plain", "Girando a la izquierda");
});

server.on("/pauseMusic", []() {
  pauseMusic();
  server.send(200, "text/plain", "parando muscia");
});
server.on("/startMusic", []() {
  startMusic();
  server.send(200, "text/plain", "iniciando musica");
});
server.on("/randomMusic", []() {
  randomMusic();
  server.send(200, "text/plain", "Musica aleatoria");
});
  // Iniciar el servidor
  server.begin();
  servos.begin();
  servos.setPWMFreq(50);

  pinMode(Minp1,OUTPUT);
  pinMode(Minp2,OUTPUT);
  pinMode(Minp3,OUTPUT);
  pinMode(Minp4,OUTPUT);

  pinMode(MpinV1,OUTPUT);
  pinMode(MpinV2,OUTPUT);

}

// Loop principal
void loop() {
  server.handleClient();
}

void moveServo(uint8_t n_servo, int startAngle, int endAngle, int stepDelay) {
  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      setServo(n_servo, angle);
      delay(stepDelay);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      setServo(n_servo, angle);
      delay(stepDelay);
    }
  }
}

void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty = map(angulo, 0, 180, pos0, pos180);
  servos.setPWM(n_servo, 0, duty);
}


// Función para manejar las acciones
void handleAction() {
  if (server.hasArg("action")) {
    String action = server.arg("action");
    
    if (action == "greeting") {
      performGreeting();
    } else if (action == "sayNo") {
      sayNo();
    } else if (action == "turnHeadRight") {
      turnHeadRight();
    } else if (action == "turnHeadLeft") {
      turnHeadLeft();
    } else if (action == "raiseNeck") {
      raiseNeck();
    } else if (action == "lowerNeck") {
      lowerNeck();
    } else if (action == "setNeckMid") {
      setNeckMid();
    } else if (action == "raiseArms") {
      raiseArms();
    } else if (action == "lowerArms") {
      lowerArms();
    } else if (action == "raiseRightArm") {
      raiseRightArm();
    } else if (action == "lowerRightArm") {
      lowerRightArm();
    } else if (action == "raiseLeftArm") {
      raiseLeftArm();
    } else if (action == "lowerLeftArm") {
      lowerLeftArm();
    }else if(action == "pauseMusic"){
      pauseMusic();
    }else if(action == "startMusic"){
      startMusic();
    }else if(action == "randomMusic"){
      randomMusic();
    }else if (action == "moveForward") {
      moveForward();
    } else if (action == "moveBackward") {
      moveBackward();
    } else if (action == "turnRight") {
      turnRight();
    }else if (action == "moveForward2") {
      moveForward2();
    }
     else if (action == "turnLeft") {
      turnLeft();
    }
     else {
      server.send(400, "text/plain", "Error: Acción desconocida");
      return;
    }

    Serial.println("Acción ejecutada: " + action);
    server.send(200, "text/plain", "Acción ejecutada: " + action);
  } else {
    server.send(400, "text/plain", "Error: No se recibió acción");
  }
}


void sayNo(){
  moveServo(6, posCabeza, 150, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(250);
  

  moveServo(6, 150, 30, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(250);

    moveServo(6, 30, 90, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(250);

  posCabeza = 90; //guardamos ultima posición;

  randomGreeting();
  }

void turnHeadRight() {
  moveServo(6, posCabeza, 150, 10);
  delay(250);
  posCabeza = 150; // Guardamos la posición final
  randomGreeting();
}

void turnHeadLeft() {
  moveServo(6, posCabeza, 30, 10);
  delay(250);
  posCabeza = 30; // Guardamos la posición final
  randomGreeting();
}

void raiseNeck() {
  moveServo(8, posCuello, 150, 10); 
  delay(250);
  posCuello = 150; // Guardamos la posición final del cuello
  randomGreeting();
}
void lowerNeck() {
  moveServo(8, posCuello, 70, 10);
  delay(250);
  posCuello = 70; // Guardamos la posición final del cuello
  randomGreeting();
}

void setNeckMid() {
  moveServo(8, posCuello, 120, 10);
  delay(250);
  posCuello = 120; // Guardamos la posición media del cuello
  randomGreeting();
}
void raiseArms(){
  moveServo(5, posBrazoD, 170, 10);  
  moveServo(7, posBrazoI, 0, 10);  
  delay(250);
  posBrazoD = 170;
  posBrazoI = 0;  
  randomGreeting();

}

void lowerArms(){
  moveServo(5, posBrazoD, 70, 10);  
  moveServo(7, posBrazoI, 90, 10);  
  delay(250);
  posBrazoD = 70;
  posBrazoI = 90;  
  randomGreeting();
}

void raiseRightArm(){
  moveServo(5, posBrazoD, 170, 10);  
  delay(250);
  posBrazoD = 170;
  randomGreeting();
}

void lowerRightArm(){
  moveServo(5, posBrazoD, 70, 10);  
  delay(250);
  posBrazoI = 70;  
  randomGreeting();

}

void raiseLeftArm(){
  moveServo(7, posBrazoD, 0, 10);  
  delay(250);
  posBrazoD = 0;
  randomGreeting();
}

void lowerLeftArm(){
  moveServo(7, posBrazoI,90, 10);  
  delay(250);
  posBrazoI = 90;  
  randomGreeting();
}

void pauseMusic(){
    dfPlayer.pause();
}
void startMusic(){
    dfPlayer.start();
}
void randomMusic(){
  playSound(random(5,22)); 
}
void performGreeting(){
  playSound(2); 
  raiseRightArm();

}

void randomGreeting(){
  int num =  random(1,10);
  if (num <= 3){
      int saludo = random(2,4);
      dfPlayer.pause();
      playSound(saludo); 
      dfPlayer.start();
  }
}

void moveForward() {
  // Configurar motores para mover hacia adelante
  digitalWrite(Minp1, LOW);
  digitalWrite(Minp2, HIGH);
  digitalWrite(MpinV1, 120); // Velocidad máxima del motor 1

  digitalWrite(Minp3, HIGH);
  digitalWrite(Minp4, LOW);
  digitalWrite(MpinV2, 120); // Velocidad máxima del motor 2
  delay(1000);
  stopMotors();
}


void moveForward2() {
  // Configurar motores para mover hacia adelante
  digitalWrite(Minp1, LOW);
  digitalWrite(Minp2, HIGH);
  digitalWrite(MpinV1, 120); // Velocidad máxima del motor 1

  digitalWrite(Minp3, HIGH);
  digitalWrite(Minp4, LOW);
  digitalWrite(MpinV2, 120); // Velocidad máxima del motor 2

}

void moveBackward() {
  // Configurar motores para mover hacia atrás
  digitalWrite(Minp1, HIGH);
  digitalWrite(Minp2, LOW);
  digitalWrite(MpinV1, 120); // Velocidad máxima del motor 1

  digitalWrite(Minp3, LOW);
  digitalWrite(Minp4, HIGH);
  digitalWrite(MpinV2, 120); // Velocidad máxima del motor 2
  delay(1000);
  stopMotors();
}

void turnRight() {
  // Configurar motores para girar hacia la derecha
  digitalWrite(Minp1, HIGH);
  digitalWrite(Minp2, LOW);
  digitalWrite(MpinV1, 120); // Velocidad máxima del motor 1

  digitalWrite(Minp3, HIGH);
  digitalWrite(Minp4, LOW);
  digitalWrite(MpinV2, 120); // Velocidad máxima del motor 2
  delay(500);
  stopMotors();
}

void turnLeft() {
  // Configurar motores para girar hacia la izquierda
  digitalWrite(Minp1, LOW);
  digitalWrite(Minp2, HIGH);
  digitalWrite(MpinV1, 120); // Velocidad máxima del motor 1

  digitalWrite(Minp3, LOW);
  digitalWrite(Minp4, HIGH);
  digitalWrite(MpinV2, 120); // Velocidad máxima del motor 2
  delay(500);
  stopMotors();
}

void stopMotors() {
  // Apagar todos los motores
  digitalWrite(Minp1, LOW);
  digitalWrite(Minp2, LOW);
  digitalWrite(MpinV1, 0);

  digitalWrite(Minp3, LOW);
  digitalWrite(Minp4, LOW);
  digitalWrite(MpinV2, 0);
}
