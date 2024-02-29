// User variables




PShape base, shoulder, upArm, loArm, end;
float rotX, rotY;
float posX=0, posY=0, posZ=0;
float alpha, beta, gamma;
float F = 50;
float T = 70;
float millisOld, gTime, gSpeed = 4;

float[] Xsphere = new float[800];
float[] Ysphere = new float[800];
float[] Zsphere = new float[800];

// Variables Draw
String word = "JC";

float cubeSize = 150;
float cubePosX = 0, cubePosY = 0, cubePosZ = -10;
int cara = 1;

float initPosX = 0; //cubeSize/2 + letterS;
float initPosY = 0; //letterH/2;
float posDX = 0, posDY = 0;
float movX = 0, movY = 0;

boolean drawing = false;
float vel = 0.1;
float presc = 0.5;
//-------------------------------------------------
// Variables Chapa
ArrayList<String> coords = new ArrayList<String>();

int index = 0;

float scale = 20, scale_factor = 2;

//Robot robot_ = null;
boolean completedPhrase = true;
//-------------------------------------------------

void writePos(float curr_x, float curr_y, float next_x, float next_y){
  IK();
  setTime();
  // Direction
  int dir_x = curr_x < next_x ? 1 : -1;
  int dir_y = curr_y < next_y ? 1 : -1;
  
  float err_x = dir_x == 1 ? abs(next_x) - abs(curr_x) : abs(curr_x) - abs(next_x);
  float err_y = dir_y == 1 ? abs(next_y) - abs(curr_y) : abs(curr_y) - abs(next_y);
  
  if( err_x > presc ) curr_x = faceMovement(next_x, true);
  if( err_y > presc ) curr_y = faceMovement(next_y, false);
  
  err_x = dir_x == 1 ? abs(next_x) - abs(curr_x) : abs(curr_x) - abs(next_x);
  err_y = dir_y == 1 ? abs(next_y) - abs(curr_y) : abs(curr_y) - abs(next_y);
  
  if( err_x < presc && err_y < presc ) index++;
  
  println("currX: " + curr_x + " currY: " + curr_y + " %%%%%%%%%%%%%%%%%%%%%%%%");
  println("posX: " + posX + " posY: " + posY + " posZ: " + posZ+ " index: " + index + " *****************");
  println("errorX: " + err_x + " errorY: " + err_y + " ##################");
  
  
  //float posDX = letterPosX(letterI);
  //float posDY = sin(gTime*PI)*10;
  //faceMovement(posDX, posDY);
}

void getCoordsFloat(ArrayList<String> coords, int j){
  if (j == coords.size()){
    completedPhrase = true;
    return;
  } else if (coords.get(j) == " ") return;
  
  String curr_coords = coords.get(j);
  
  float[] p_coords = {0,0,0,0};
  String dummy = "";
  int f_index = 0;
  for (int i = 0; i < curr_coords.length(); i++){
    if (curr_coords.charAt(i) == ',' || curr_coords.charAt(i) == ';'){
      System.out.print(dummy + ";  ");
      p_coords[f_index++] = Float.parseFloat(dummy);
      dummy = "";
      continue;
    }
    
    dummy += curr_coords.charAt(i);
  }
  
  System.out.println("---------");
  
  float curr_x = p_coords[0], curr_y = p_coords[1], next_x = p_coords[2], next_y = p_coords[3];
  writePos(curr_x, curr_y, next_x, next_y);
}

float letterPosX(int i){
  float position = ( cubeSize / word.length()) * i - (cubeSize/2) + 3;
  println(position);
  return position;
}

// Updates the position depending on the face selected
float faceMovement(float posD, boolean isX){
  switch(cara){
    case 1:
      if(isX) posY = lerp(posY,posD,vel);
      else posX = lerp(posX,posD,vel);
      posZ = -cubeSize/2 + cubePosZ*2;
      return isX ? posY : posX;
    case 2:
      if(isX) posY = lerp(posY,posD,vel);
      else posZ = lerp(posZ,posD,vel) + cubePosZ*2;
      posX = cubeSize/2;
      return isX ? posY : posX;
    case 3:
      if(isX) posX = lerp(posX,posDX,vel);
      else posZ = lerp(posZ,posDY,vel) + cubePosZ*2;
      posY = cubeSize/2;
      return isX ? posX : posZ;
    case 4:
      if(isX) posY = lerp(posY,posD,vel);
      else posZ = lerp(posZ,posD,vel) + cubePosZ*2;
      posX = -cubeSize/2;
      return isX ? posY : posZ;
    case 5:
      if(isX) posX = lerp(posX,posD,vel);
      else posZ = lerp(posZ,posD,vel) + cubePosZ*2;
      posY = -cubeSize/2;
      return isX ? posX : posZ;
    case 6:
      println("Nel");
      return 0.0;
  }
  
  return 0.0;
}

// Updates the position depending on the face selected
void faceMovement(float posDX, float posDY){
  switch(cara){
    case 1:
      posY = posDX;
      posX = posDY;
      posZ = -cubeSize/2 + cubePosZ*2;
    break;
    case 2:
      posY = posDX;
      posZ = posDY + cubePosZ;
      posX = cubeSize/2;
    break;
    case 3:
      posX = posDX;
      posZ = posDY + cubePosZ;
      posY = cubeSize/2;
    break;
    case 4:
      posY = posDX;
      posZ = posDY + cubePosZ;
      posX = -cubeSize/2;
    break;
    case 5:
      posX = posDX;
      posZ = posDY + cubePosZ;
      posY = -cubeSize/2;
    break;
    case 6:
      println("Nel");
    break;
  }
}

// Transposes the coordinates to the selected face
float[] facePosition(float X, float Y){
  switch(cara){
    case 1:
      X -= posY + initPosX; 
      Y -= posX + initPosY; 
    break;
    case 2:
      X -= posY + initPosX; 
      Y -= posZ + initPosY; 
    break;
    case 3:
      X -= posX + initPosX; 
      Y -= posZ + initPosY; 
    break;
    /*
    case 4:
      posY = posDX;
      posZ = posDY + cubePosZ;
      posX = -cubeSize/2;
    break;
    case 5:
      posX = posDX;
      posZ = posDY + cubePosZ;
      posY = -cubeSize/2;
    break;
    case 6:
      println("Nel");
    break;
    */
    }
    float[] results = {X, Y};
    return results;
}

void IK(){
  float X = posX;
  float Y = posY;
  float Z = posZ;

  float L = sqrt(Y*Y+X*X);
  float dia = sqrt(Z*Z+L*L);

  alpha = PI/2-(atan2(L, Z)+acos((T*T-F*F-dia*dia)/(-2*F*dia)));
  beta = -PI+acos((dia*dia-T*T-F*F)/(-2*F*T));
  gamma = atan2(Y, X);
}

void setTime(){
  gTime += ((float)millis()/1000 - millisOld)*(gSpeed/4);
  if(gTime >= 4)  gTime = 0;  
  millisOld = (float)millis()/1000;
}

void robotSetup(){
  base = loadShape("r5.obj");
  shoulder = loadShape("r1.obj");
  upArm = loadShape("r2.obj");
  loArm = loadShape("r3.obj");
  end = loadShape("r4.obj");
  
  shoulder.disableStyle();
  upArm.disableStyle();
  loArm.disableStyle(); 
  
  // J hardcodeada
  // Scaled coordinates
  float curr_x = 0.0 * scale/scale_factor, curr_y = 0.0 * scale; 
  float next_x = 1.0 * scale/scale_factor, next_y = 0.0 * scale;
  // Transposed coordinates
  float[] temp = facePosition(curr_x, curr_y); curr_x = temp[0]; curr_y = temp[1];
  temp = facePosition(next_x, next_y); next_x = temp[0]; next_y = temp[1];
  // Add coordinates
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
  // Repeat
  curr_x = 1.0 * scale/scale_factor; curr_y = 0.0 * scale; 
  next_x = 2.0 * scale/scale_factor; next_y = 0.0 * scale;
  temp = facePosition(curr_x, curr_y); curr_x = temp[0]; curr_y = temp[1];
  temp = facePosition(next_x, next_y); next_x = temp[0]; next_y = temp[1];
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
  curr_x = 2.0 * scale/scale_factor; curr_y = 0.0 * scale; 
  next_x = 2.0 * scale/scale_factor; next_y = 1.0 * scale;
  temp = facePosition(curr_x, curr_y); curr_x = temp[0]; curr_y = temp[1];
  temp = facePosition(next_x, next_y); next_x = temp[0]; next_y = temp[1];
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
  curr_x = 2.0 * scale/scale_factor; curr_y = 1.0 * scale; 
  next_x = 2.0 * scale/scale_factor; next_y = 2.0 * scale;
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
  curr_x = 2.0 * scale/scale_factor; curr_y = 2.0 * scale; 
  next_x = 1.0 * scale/scale_factor; next_y = 2.0 * scale;
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
  curr_x = 1.0 * scale/scale_factor; curr_y = 2.0 * scale; 
  next_x = 0.0 * scale/scale_factor; next_y = 2.0 * scale;
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
  curr_x = 0.0 * scale/scale_factor; curr_y = 2.0 * scale; 
  next_x = 0.0 * scale/scale_factor; next_y = 1.0 * scale;
  coords.add(curr_x + "," + curr_y + "," + next_x + "," + next_y + ";");
}

void updatePos(){
   if(completedPhrase){
     System.out.println("------------------------------");
     //face = 1;
     index = 0;
     faceMovement(initPosX,initPosY);
     //robot_.coords.clear();
     //robot_.writePhrase(phrase);
     //for (String ss : robot_.coords) System.out.println(ss + " "); 
     System.out.println("------------------------------");
     completedPhrase = false;
   }
   
   getCoordsFloat(coords, index);
   
   background(#54a5e8);
   smooth();
   lights(); 
   directionalLight(51, 102, 126, -1, 0, 0);
    
    for (int i=0; i< Xsphere.length - 1; i++) {
    Xsphere[i] = Xsphere[i + 1];
    Ysphere[i] = Ysphere[i + 1];
    Zsphere[i] = Zsphere[i + 1];
    }
    
    Xsphere[Xsphere.length - 1] = posX;
    Ysphere[Ysphere.length - 1] = posY;
    Zsphere[Zsphere.length - 1] = posZ;
   
   noStroke();
   
   translate(width/2,height/2);
   rotateX(rotX);
   rotateY(-rotY);
   scale(-4);
   
   for (int i=0; i < Xsphere.length; i++) {
     pushMatrix();
     translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
     fill (#D003FF);
     sphere(2);
     popMatrix();
    }
    
   stroke(#000000);
   noFill();
   translate(-cubePosY, -cubePosZ, -cubePosX);
   box(cubeSize);
   
   noStroke();
    
   fill(#FFE308);  
   translate(cubePosY,-40+cubePosZ,cubePosX);   
     shape(base);
     
   translate(0, 4, 0);
   rotateY(gamma);
     shape(shoulder);
      
   translate(0, 25, 0);
   rotateY(PI);
   rotateX(alpha);
     shape(upArm);
      
   translate(0, 0, 50);
   rotateY(PI);
   rotateX(beta);
     shape(loArm);
      
   translate(0, 0, -50);
   rotateY(PI);
     shape(end);
}

void setup(){
    size(1200, 800, OPENGL);
    robotSetup();
}

void draw(){ 
   updatePos();
}

void mouseDragged(){
    rotY -= (mouseX - pmouseX) * 0.01;
    rotX -= (mouseY - pmouseY) * 0.01;
}
