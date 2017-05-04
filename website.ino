static String startpage =
"<html>\n"
"<head>\n"
"  <title>Bottle Lamp</title>\n"
"  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"
"</head>\n"
"<body>\n"
"<style>\n"
"body {\n"
"  background: #333333;\n"
"  color: white;\n"
"  font-family: \"sans\";\n"
"  font-size: 1.5em;\n"
"}\n"
"input {\n"
"  width: 99%;\n"
"}\n"
".nav {\n"
"  background: #555555;\n"
"  padding: 0.2em;\n"
"  list-style: none;\n"
"  overflow-x: scroll;\n"
"  white-space:nowrap\n"
"}\n"
".nav li {\n"
"  display: inline-block;\n"
"  padding: 0 5px 0 8px;\n"
"}\n"
".nav a {\n"
"  color: #fff;\n"
"}\n"
"</style>\n"
"<script>\n"
"function animation(e, a) {\n"
"  send(e, \"a/\" + a);\n"
"  controlBox(a);\n"
"}\n"
"function send(e, u){\n"
"  req = new XMLHttpRequest();\n"
"  req.open(\"GET\", u, false);\n"
"  req.send(null);\n"
"}\n"
"function controlBox(a){\n"
"  boxes = document.querySelectorAll(\".animation\");\n"
"  for (i=0; i<boxes.length; i++){\n"
"    boxes[i].style.display = \"none\";\n"
"  }\n"
"  box = document.getElementById(a);\n"
"  box.style.display = \"block\";\n"
"}\n"
"</script>\n"
"<div class=\"header\">\n"
"  <ul class=\"nav\">\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'black')\">black</a></li>\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'rainbow')\">rainbow</a></li>\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'fire')\">fire</a></li>\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'color_solid')\">color</a></li>\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'color_bubbling')\">color_bubbling</a></li>\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'juggle')\">juggle</a></li>\n"
"    <li><a href=\"#\" onclick=\"animation(this, 'sinelon')\">sinelon</a></li>\n"
"  </ul>\n"
"  <div>\n"
"      <label for=\"brightness\">Brightness</label>\n"
"      <input type=\"range\" min=\"0\" max=\"255\" value=\"255\" name=\"brightness\" onchange=\"send(this, 'brightness?b=' + this.value)\">\n"
"  </div>\n"
"</div>\n"
"<div class=\"container\">\n"
"  <hr>\n"
"  <div class=\"animation\" id=\"black\">\n"
"    <h2>Black</h2>\n"
"  </div>\n"
"  <div class=\"animation\" id=\"rainbow\">\n"
"    <h2>Rainbow</h2>\n"
"    <label for=\"r_speed\">speed</label>\n"
"    <input type=\"range\" min=\"0\" max=\"70\" value=\"20\" name=\"r_speed\" onchange=\"send(this, 'a/rainbow?s=' + this.value)\">\n"
"    <label for=\"r_width\">width</label>\n"
"    <input type=\"range\" min=\"0\" max=\"20\" value=\"7\" name=\"r_width\" onchange=\"send(this, 'a/rainbow?w=' + this.value)\">\n"
"  </div>\n"
"  <div class=\"animation\" id=\"fire\">\n"
"    <h2>Fire</h2>\n"
"  </div>\n"
"  <div class=\"animation\" id=\"color_solid\">\n"
"    <h2>Color</h2>\n"
"    <label for=\"c_color\">Color</label>\n"
"    <input type=\"color\" name=\"c_color\" onchange=\"send(this, 'a/color_solid?c=' + this.value.slice(1))\">\n"
"  </div>\n"
"  <div class=\"animation\" id=\"color_bubbling\">\n"
"    <h2>Color_bubbling</h2>\n"
"    <label for=\"b_color\">Color</label>\n"
"    <input type=\"color\" name=\"b_color\" onchange=\"send(this, 'a/color_bubbling?c=' + this.value.slice(1))\">\n"
"    <label for=\"b_on\">on</label>\n"
"    <input type=\"range\" min=\"0\" max=\"255\" value=\"20\" name=\"b_on\" onchange=\"send(this, 'a/color_bubbling?on=' + this.value)\">\n"
"    <label for=\"b_off\">off</label>\n"
"    <input type=\"range\" min=\"0\" max=\"255\" value=\"7\" name=\"b_off\" onchange=\"send(this, 'a/color_bubbling?off=' + this.value)\">\n"
"  </div>\n"
"  <div class=\"animation\" id=\"juggle\">\n"
"    <h2>Juggle</h2>\n"
"  </div>\n"
"  <div class=\"animation\" id=\"sinelon\">\n"
"    <h2>Sinelon</h2>\n"
"  </div>\n"
"</div>\n"
"</body>\n"
;

void serverSetup() {
  server.on("/", handleRoot);
  server.on("/brightness", handleBrightness);
  server.on("/brightness/inc", handleIncBrightness);
  server.on("/brightness/dec", handleDecBrightness);

  server.on("/a/black", handleAnimationBlack);
  server.on("/a/rainbow", handleAnimationRainbow);
  server.on("/a/fire", handleAnimationFire);
  server.on("/a/color_solid", handleColorSolid);
  server.on("/a/color_bubbling", handleColorBubbling);
  server.on("/a/juggle", handleJuggle);
  server.on("/a/sinelon", handleSinelon);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}


void handleRoot() {
  digitalWrite(LED_BUILTIN, 1);
  server.send(200, "text/html", startpage);
  digitalWrite(LED_BUILTIN, 0);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleBrightness() {
  if (server.hasArg("b")){
    int a = server.arg("b").toInt();
    brightness = std::max(0, std::min(a, 255));
    FastLED.setBrightness(brightness);
    }
  server.send(200, "text/plan", (String) brightness);
}

void handleIncBrightness() {
  brightness = std::min(brightness + 5, 255);
  FastLED.setBrightness(brightness);
  server.send(200, "text/plan", (String) brightness);
}

void handleDecBrightness() {
  brightness = std::max(brightness - 5, 0);
  FastLED.setBrightness(brightness);
  server.send(200, "text/plan", (String) brightness);
}

void handleAnimationBlack(){
  animation = &black;
  server.send(200);
}

void handleAnimationRainbow(){
  if (server.hasArg("s")){
    int s = server.arg("s").toInt();
    rainbow_speed = s;
  }
  if (server.hasArg("w")){
    int w = server.arg("w").toInt();
    rainbow_width = w;
  }
  animation = &rainbow;
  server.send(200);
}

void handleAnimationFire(){
  animation = &Fire2012;
  server.send(200);
}

void handleColorSolid(){
  if (server.hasArg("c")){
   String a = server.arg("c");
    user_color = strtoul(a.c_str(), NULL, 16);
    Serial.println(a);
  }
  animation = &color_solid;
  Serial.println("switched");
  server.send(200);
}

void handleColorBubbling(){
  if (server.hasArg("c")){
   String a = server.arg("c");
    user_color = strtoul(a.c_str(), NULL, 16);
  }
  if (server.hasArg("on")){
    int o = server.arg("on").toInt();
    bubbling_on_chance = o;
  }
  if (server.hasArg("off")){
    int o = server.arg("off").toInt();
    bubbling_off_threashold = o;
  }
  animation = &color_bubbling;
  server.send(200);
}

void handleJuggle(){
  animation = &juggle;
  server.send(200);
}

void handleSinelon(){
  animation = &sinelon;
  server.send(200);
}
