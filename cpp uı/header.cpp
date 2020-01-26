#include "header.h"	
#include <Windows.h>		

#define HEADERMESSAGE "camera connection failed ! "
#define CONTENTMESSAGE "Camera ERROR"

#define WARNINGLIMIT 95




//// CLASS MOUSE

void Mouse::resetMouseClickCoord()
{
	pStart =  { 0, 0 };
	pFinish = { 0, 0 };
}
void Mouse::mouseClickCoordSet() {
	// Mouse ile heryone dogru secim yapilabilmesi icin click kordinatlarý duzenlenir

	// pStart -> kesme yapilinca baslangic noktasi,  pFinish-> kesme sonrasi bitis noktasi

	if (pFinish.x - pStart.x < 0 && pFinish.y - pStart.y > 0)					// sagdan sola asagi dogru secim icin point kordinatlarini duzenle
		swapClickPointX();														// baslangic ve bitis noktalarinin X kordinatlarini swap la  

	else if (pFinish.x - pStart.x > 0 && pFinish.y - pStart.y < 0)				// soldan saga yukari dogru secim icin point kordinatlarini duzenle
		swapClickPointY();														// baslangic ve bitis noktalarinin Y kordinatlarini swap la 

	else if (pFinish.x - pStart.x < 0 && pFinish.y - pStart.y < 0) {			// sagdan sola yukari dogru secim icin point kordinatlarini duzenle
		swapClickPointX();
		swapClickPointY();

	}
	// soldan saga asagi dogru secimde parametrelerin bitis nokta kordinatlari, baslangic nokta kordinatlarindan buyuk olacagindan duzenlemesine gerek yok

	// en kucuk secim bir týklama ise ( width veya height == 0 ise ) en kucuk 5*5 lik karo sec
	else if (pFinish.x - pStart.x == 0 || pFinish.y - pStart.y == 0) {
		pFinish.x = pStart.x + 5;
		pFinish.y = pStart.y + 5;
	}
}
cv::Point& Mouse::getStartPoint() {
	return pStart;
}
cv::Point& Mouse::getFinishPoint() {
	return pFinish;
}
// swapClickPoint secimin baslangic ve bitis noktalarini swap yapar
void Mouse::swapClickPointX() {
	pStart.x = pStart.x + pFinish.x;
	pFinish.x = pStart.x - pFinish.x;
	pStart.x = pStart.x - pFinish.x;
	
}
void Mouse::swapClickPointY() {
	pStart.y = pStart.y + pFinish.y;
	pFinish.y = pStart.y - pFinish.y;
	pStart.y = pStart.y - pFinish.y;
}
void Mouse::setStartPointX(int x)
{
	pStart.x = x;
}
void Mouse::setStartPointY(int y)
{
	pStart.y = y;
}
void Mouse::setFinishPointX(int x)
{
	pFinish.x = x;
}
void Mouse::setFinishPointY(int y)
{
	pFinish.y = y;
}



// CLASS DISPLAY 

double Display::getFpsDisplay(cv::VideoCapture& cap )		// goruntunun FPS degerini dondur
{
	return cap.get(cv::CAP_PROP_FPS);
}
void Display::writeFpsDisplay(cv::Mat& camFrame, std::string Text)			// goruntu uzerine FPS degerini yaz
{
	cv::Point upperRightCorner(camFrame.cols - 40, 30);		// Gorunutunun sag ust kosesi icin kordinatlar
	cv::Scalar Green(0, 255, 0);							// RGB yesil renk degeri
	int fpsFontSize = 1;									// FPS Text buyuklugu
	int fpsTextThickness = 1;								// FPS Text kalinligi

	// Goruntu matrisi, Text , Baslangic noktasi, Text Font u , Text buyuklugu , RGB degerleri, Kalinlik
	
	putText(camFrame, Text, upperRightCorner , cv::FONT_HERSHEY_SIMPLEX, fpsFontSize, Green, fpsTextThickness); 
}
void Display::showFpsDisplay(cv::VideoCapture& cap, cv::Mat& camFrame)		// FPS degerini goster
{
	double FPS = getFpsDisplay(cap);
	writeFpsDisplay(camFrame, std::to_string(FPS));
}
void Display::videoCapture(cv::VideoCapture&  cap, cv::Mat& camFrame)
{
	cap >> camFrame;
}
void Display::videoDisplay(cv::Mat& camFrame, const char * mainWindowName)
{
	cv::imshow(mainWindowName, camFrame); // MAINWINDOWNAME adýnda yeni bir pencere oluþtur ve camFrame'i o pencerede göster.
}
void Display::createWindow(const char * mainwWindowName)
{
	cv::namedWindow(mainwWindowName, cv::WINDOW_AUTOSIZE);		// ana pencereyi MAINWINDOWNAME ismi ile yarat
}
void Display::drawRectangleDisplay(cv::Mat& camFrame, Mouse& mouseObject)
{
	cv::Scalar greenLine(0, 255, 0);
	int lineThickness = 2;
	rectangle(camFrame, cv::Point(mouseObject.getStartPoint().x, mouseObject.getStartPoint().y), cv::Point(mouseObject.getFinishPoint().x, mouseObject.getFinishPoint().y), greenLine, lineThickness);		
}


// CLASS CONTROL

// kamera ile yapilan baglanti kontrol edilir
void Controls::camConnectionControl(cv::VideoCapture& cap, const int camIndex)
{
	if (!cap.open(camIndex))					// 0 indexli camera acilmadi mi
	{
		connectionErrorMessageShow();			// Baglanti hatasi mesajini goster ve cik
	}
}
void Controls::connectionErrorMessageShow()
{
	// Sesin Frekansi(hertz), Sesin suresi(ms)
	Beep(750, 300);
	// Mesaj kutusu -> mesaj basligi, mesaj icerigi, mesaj kutusu butonu, mesaj kutusu ikonu
	System::Windows::Forms::MessageBox::Show( HEADERMESSAGE, CONTENTMESSAGE, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	
	exit(EXIT_FAILURE);					// Hata ile cik	
}
// camFrame nesnesi kontrol edilir
bool Controls::isCamFrameEmpty(cv::Mat& camFrame)
{
	return camFrame.empty();
}



// CLASS PREOBJECTDETECTION

PreObjectDetection::PreObjectDetection()
{
	resetPreObjectDetectionVariables();
}
void PreObjectDetection::resetPreObjectDetectionVariables()
{
	hsvFrame = { NULL };
	objectHist = { NULL };
	blackZoneMask = { NULL };
	cropHsvFrame = { NULL };
	cropMask = { NULL };
	
}
void PreObjectDetection::setCropRectangle(cv::Point pStart, cv::Point pFinish){
	int width = pFinish.x - pStart.x;
	int height = pFinish.y - pStart.y;
	cropRectangle = cv::Rect(pStart.x, pStart.y, width, height);
}
void PreObjectDetection::RGB2HSV(cv::Mat& camFrame)
{
	// orginal frame, donusum sonucu atanacak matris, donusum formati (BGR -> HSV)
	cvtColor(camFrame, hsvFrame, cv::COLOR_BGR2HSV);
}
void PreObjectDetection::hsvMasking()
{
	// karanlik alanlari ekrandan kaldirmak icin hsvFrame matrisine Scalar degerler arasi maskeleme yap ve blackZoneMask matrisine aktar
	inRange(hsvFrame, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), blackZoneMask);
}
void PreObjectDetection::calculateHistogram()
{
	// calcHist iþlevi bir veya daha fazla dizinin histogramýný hesaplar. 
	/*  calcHist(
		Histogrami hesaplanacak source image,
		source image sayisi,
		Histogramý hesaplamak için kullanýlan karartma kanallarýnýn listesi,
		Maskeleme yapilicaksa maske matrisi,
		Output histogram,
		Histogram boyutlugu -> pozitif olmali,
		Her boyuttaki histogram boyutlarýnýn dizisi,
		Her boyuttaki histogram kutusu sýnýrlarýnýn karartma dizileri dizisi
	)
	*/
	// maskRoi ile maskelenmis histogram uygula ve objectHist matrisine yerlestir
	calcHist(&cropHsvFrame, 1, channels, cropMask, objectHist, 1, histSize, histRange);
}
void PreObjectDetection::normalizeObjectHist()
{
	// Nesnenin homografisini normalleþtirir
	/* normalize(
			input Mat,
			output Mat,
			Normalizasyon alt sýnýr,
				``		  ust sinir,
				``		  turu
	)
	*/
	normalize(objectHist, objectHist, 0, 255, cv::NORM_MINMAX);
}
void PreObjectDetection::preDetection(cv::Mat& camFrame){

	RGB2HSV(camFrame);				// ekran goruntusunu RGB -> HSV donustur

	hsvMasking();					// HSV matrisinde karanlik bolgeleri maskele ve mask Matrisine aktar

	cropHsvFrame = cv::Mat(hsvFrame, cropRectangle);		// kesilen matris ozelliklerinde hsv mastrisnden kes (ayni kordinatalara sahip)
	cropMask = cv::Mat(blackZoneMask, cropRectangle);		// aynisini maskelenmis matrise yap
	

	calculateHistogram();		// maskRoi ile maskelenmis histogram hesapla => objectHist

	normalizeObjectHist();		// objectHist matrisini normalizle
}
cv::Mat PreObjectDetection::getObjectHistogram()
{
	return objectHist;
}
cv::Rect PreObjectDetection::getCropRectangle()
{
	return cropRectangle;
}



// CLASS OBJECTDETECTION

ObjectDetection::ObjectDetection()
{
	resetObjectDetectionVariables();
}
void ObjectDetection::resetObjectDetectionVariables()
{
	outputBackProject = { NULL };
	hsvFrame = { NULL };
	detectionPoints[0] = { (float)0.0, (float)0.0 };
	detectionPoints[1] = { (float)0.0, (float)0.0 };
	detectionPoints[2] = { (float)0.0, (float)0.0 };
	detectionPoints[3] = { (float)0.0, (float)0.0 };
}
void ObjectDetection::detectionDraw(cv::Mat& camFrame){

	int numberOfPoints = 4;
	cv::Scalar greenLine(0, 255, 0);
	int lineThickness = 2;
	// bulunan noktalari cizgi ile birlestir 
	for (int pointIndex = 0; pointIndex < numberOfPoints; pointIndex++)
		line(camFrame, detectionPoints[pointIndex], detectionPoints[(pointIndex + 1) % 4], greenLine, lineThickness);		// 4 noktayi green line ile belirt

}
int ObjectDetection::markDirectionsObject(cv::Mat& camFrame)
{
	// sag = 1, sol = 2, yukari = 3 , asagi = 4, bos = 0
	
	// turn right
	if (detectionPoints[3].x >= camFrame.cols - WARNINGLIMIT || detectionPoints[4].x >= camFrame.cols - WARNINGLIMIT)	
	{
		// saga dogru sinyal ver
		return 1;
	}
	// turn left
	else if (detectionPoints[0].x <= WARNINGLIMIT || detectionPoints[1].x <= WARNINGLIMIT)	
	{
		return 2;
	}
	// turn down
	else if (detectionPoints[0].y >= (camFrame.rows - WARNINGLIMIT ) || detectionPoints[3].y >= (camFrame.rows - WARNINGLIMIT ))	
	{
		return 3;
	}
	// turn up
	else if (detectionPoints[1].y <= WARNINGLIMIT  || detectionPoints[2].y <= WARNINGLIMIT )	
	{
		return 4;
	}
	return 0;
}

