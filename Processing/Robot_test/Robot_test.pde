import java.util.LinkedList;
import java.util.Queue;

PShape base, shoulder, upArm, loArm, end;
float rotX, rotY;
float posX=1, posY=50, posZ=50, posD1 = -600, posD2 = -600;
float alpha, beta, gamma;
float F = 50;
float T = 70;
float millisOld, gTime, gSpeed = 4;

boolean draw = false;
boolean completedLine = true, filledInstructs = false, completedLetter = true;
String name = "Paco";
int iName = -1;
Queue<Integer> instr = new LinkedList<>();
int instruction = 0;

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
  if(gTime >= 100)  gTime = 0;  
  millisOld = (float)millis()/1000;
}

void writePos(){
  IK();
  setTime();
  if(gTime < 5){
    posY = 80;
    posX = 80;
    posZ = 10;
  }
  
  if(5 < gTime && gTime < 10){
    draw = false;
    forwardSlash(1);
    println("Done1");
  }
  completedLine = false;
  if(10 < gTime && gTime < 15){
    draw = true;
    forwardSlash(1);
    println("Done2");
  }
  completedLine = false;
  if(15 < gTime && gTime < 20){
    draw = true;
    forwardSlash(-1);
    println("Done3");
  }
  
  /*
  else{
    draw = true;
    //forwardSlash(1);
    
    
    println("Line:" + completedLine + " Instr:" + filledInstructs + " Letter:" + completedLetter + " iName:" + iName);
    if(completedLetter){
      iName += 1;
      completedLetter = false;
    }
    else{
      if(iName >= name.length()){
        gTime = 0;
        iName = -1;
        instruction = 0;
        completedLetter = true;
      }
      else{
        writeLetter();
      }
    }
    
  }*/
}

void writeLetter(){
  if(instr.isEmpty() && filledInstructs == false){
    switch(name.charAt(iName)){
      case 'P':
      case 'p':
        instr.add(1);instr.add(1);instr.add(3);instr.add(3);instr.add(5);instr.add(7);instr.add(7);instr.add(-5);instr.add(-3);instr.add(-3);instr.add(-3);
        break;
      case 'A':
      case 'a':
        instr.add(1);instr.add(1);instr.add(3);instr.add(3);instr.add(5);instr.add(5);instr.add(-1);instr.add(7);instr.add(7);instr.add(-5);instr.add(-3);instr.add(-3);instr.add(-3);
        break;
      case 'C':
      case 'c':
        instr.add(1);instr.add(1);instr.add(3);instr.add(3);instr.add(-5);instr.add(-5);instr.add(7);instr.add(7);instr.add(-3);instr.add(-3);instr.add(-3);
        break;
      case 'O':
      case 'o':
        instr.add(1);instr.add(1);instr.add(3);instr.add(3);instr.add(5);instr.add(5);instr.add(7);instr.add(7);instr.add(-3);instr.add(-3);instr.add(-3);
        break;
      
    }
  }
  else if(instr.isEmpty() && filledInstructs == true && completedLine){
    completedLetter = true;
    filledInstructs = false;
  }
  else{
    writeLine();
  }
}

void writeLine(){
  if(completedLine){
    instruction = instr.remove();
    completedLine = false;
  }
  switch(instruction){
    case 1:
      verticalLine(1);
      break;
    case 2:
      forwardSlash(1);
      break;
    case 3:
      horizontalLine(1);
      break;
    case 4:
      backSlash(-1);
      break;
    case 5:
      verticalLine(-1);
      break;
    case 6:
      forwardSlash(-1);
      break;
    case 7:
      horizontalLine(-1);
      break;
    case 8:
      backSlash(1);
      break;
    case -1:
      draw = false;
      verticalLine(1);
      break;
    case -2:
      draw = false;
      forwardSlash(1);
      break;
    case -3:
      draw = false;
      horizontalLine(1);
      break;
    case -4:
      draw = false;
      backSlash(-1);
      break;
    case -5:
      draw = false;
      verticalLine(-1);
      break;
    case -6:
      draw = false;
      forwardSlash(-1);
      break;
    case -7:
      draw = false;
      horizontalLine(-1);
      break;
    case -8:
      draw = false;
      backSlash(1);
      break;
  }
}

void verticalLine(int dir, x, z){
  println("D:" + posD1 + " Z:" + posZ);
  if(posD1 == 0) posD1 = posZ - z * dir;
  if( (posZ * dir) <= (posD1 * dir) ){
    posD1 = 0;
    completedLine = true; 
  }
  if( (posZ * dir) > (posD1 * dir) ) posZ = posZ - 1 * dir;
}

void horizontalLine(int dir){
  if(posD1 == 0) posD1 = posX - 5 * dir;
  if( (posX * dir) <= (posD1 * dir) ){
    posD1 = 0;
    completedLine = true; 
  }
  if( (posX * dir) > (posD1 * dir) ) posX = posX - 0.5 * dir;
}

void forwardSlash(int dir){
  println("Atorado: " + completedLine);
  if(posD1 == 0) posD1 = posX - x * dir;
  if(posD2 == 0) posD2 = posZ - z * dir;
  if( (posX * dir) < (posD1 * dir) ){
    posD1 = 0;
    posD2 = 0;
    completedLine = false; 
  }
  if( (posX * dir) > (posD1 * dir) ) posX = posX - 0.5 * dir;
  if( (posZ * dir) > (posD2 * dir) ) posZ = posZ - 1 * dir;
}

void backSlash(int dir){
  if(posD1 == 0) posD1 = posX + 5 * dir;
  if(posD2 == 0) posD2 = posZ - 10 * dir;
  if( (posX * dir) < (posD1 * dir) ) posX = posX + 0.5 * dir;
  if( (posZ * dir) > (posD2 * dir) ) posZ = posZ - 1 * dir;
  if( (posX * dir) > (posD1 * dir) && (posZ * dir) < (posD2 * dir) ){
    posD1 = 0;
    posD2 = 0;
    completedLine = true; 
  }
}

float[] Xsphere = new float[1000];
float[] Ysphere = new float[1000];
float[] Zsphere = new float[1000];

void setup(){
    size(1200, 800, OPENGL);
    
    base = loadShape("r5.obj");
    shoulder = loadShape("r1.obj");
    upArm = loadShape("r2.obj");
    loArm = loadShape("r3.obj");
    end = loadShape("r4.obj");
    
    shoulder.disableStyle();
    upArm.disableStyle();
    loArm.disableStyle(); 
}

void draw(){ 
   writePos();
   background(32);
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
   
   if(draw){
   for (int i=0; i < Xsphere.length; i++) {
     pushMatrix();
     translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
     fill (#D003FF);
     sphere (1.5);
     popMatrix();
    }
   }
    
   fill(#FFE308);  
   translate(0,-40,0);   
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

void mouseDragged(){
    rotY -= (mouseX - pmouseX) * 0.01;
    rotX -= (mouseY - pmouseY) * 0.01;
}
