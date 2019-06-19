const int sampleWindow = 50;      // 샘플링한 시간 50ms
unsigned int value;               // 소리 증폭 감지 센서 값 받는 변수

int led[8] = {2, 3, 4, 5, 6, 7, 8, 9 };   // led 8개의 핀 번호 2~9
int sound_value ;

void setup() {
  for(int i=0; i<8; i++)             // led 8개를 출력으로 설정
    pinMode(led[i], OUTPUT);
    
   Serial.begin(9600);              // 시리얼 모니터 시작, 속도는 9600
}
 
void loop() {
   unsigned long startMillis= millis();  // 샘플링 시작
   unsigned int peakToPeak = 0;          // 음성 신호의 진폭
 
   unsigned int signalMax = 0;           // 최대 크기를 초기에는 0으로 설정
   unsigned int signalMin = 1024;        // 최소 크기를 초기에는 1024로 설정
 
   while (millis() - startMillis < sampleWindow){  // 데이터를 50ms마다 모으는 while문
      value = analogRead(A0);           // 소리 감지센서에더 데이터 받아오기
      if (value < 1024){                // 받아온 데이터의 값이 1024 이하일 때
         if (value > signalMax)         // 최대 크기 측정
            signalMax = value;          // 최대 크기 signalMax에 저장
         else if (value < signalMin)    // 최소 크기 측정
            signalMin = value;          // 최소 크기 sigmalMin에 저장
      }
   }
   
   peakToPeak = signalMax - signalMin;  // 최대- 최소 = 진폭값
   double volts = (peakToPeak * 5.0) / 1024;  // 전압 단위로 변환 = 소리 크기로 변환
   
   int i, j, k;
   
   for(i = 0; i < 8; i++){            // 소리크리를 led로 출력하기 위해 계산
    float cal = i;
    if(cal*0.40 < volts && ((cal+1)*0.40) > volts)    // 소리 크기가 어느 led까지 켜지게 되는지 계산
      sound_value = i;
   }

   for(int j = 0; j < 8; j++){   // 해당되는 led 까지 led on
    if(j < sound_value) 
      digitalWrite(led[j], HIGH);
    else 
      digitalWrite(led[j], LOW); 
   }
   Serial.println(volts);
}
