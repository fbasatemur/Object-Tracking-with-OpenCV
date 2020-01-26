#pragma once
#include<opencv2/core/types.hpp>
#include<opencv2/video/tracking.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>


class Mouse
{
public:
	void resetMouseClickCoord();			// mouse verileri resetlenir
	void mouseClickCoordSet();				// mouse ile heryone dogru secim yapilabilmesi icin paramerelerin uygunlugunu kontrol eder
	void swapClickPointX();					// pStart ve pFinish noktalarinin X eksenin kordinat degerlerini swap lar
	void swapClickPointY();					// pStart ve pFinish noktalarinin Y eksenin kordinat degerlerini swap lar

	cv::Point& getStartPoint();				// pStart point nesnesini return et
	cv::Point& getFinishPoint();			// pFinish point nesnesini return et

	void setStartPointX(int);
	void setStartPointY(int);
	void setFinishPointX(int);
	void setFinishPointY(int);


private:
	cv::Point pStart, pFinish;					// pStart -> kesme yapilinca baslangic noktasi,  pFinish-> kesme sonrasi bitis noktasi
};



class Display
{
public:

	double getFpsDisplay(cv::VideoCapture &);				// camFrame uzerinden FPS degerini oku
	void writeFpsDisplay(cv::Mat& , std::string);			// camFrame uzerine FPS degerini yaz
	void showFpsDisplay(cv::VideoCapture& , cv::Mat& );		// camFrmae uzerine FPS degerini yerlestirir
	void videoCapture(cv::VideoCapture& , cv::Mat& );		// cam den goruntuyu camFrame e oku
	void videoDisplay(cv::Mat&, const char *);				// camFrame nesnesini ekrana yansit
	void createWindow(const char *);						// arguman isminde pencere yarat
	void drawRectangleDisplay(cv::Mat&, Mouse& );			// goruntuye dikdortgen ciz
};



class Controls
{
public:

	void camConnectionControl(cv::VideoCapture& ,const int);	// camera baglantisini kontrol eder
	void connectionErrorMessageShow();							// cam baglantisinda olusan hata pencersini gosterir
	bool isCamFrameEmpty(cv::Mat& );							// camFrame bos mu

};



class PreObjectDetection
{
public:
	PreObjectDetection();
	void resetPreObjectDetectionVariables();
	void setCropRectangle(cv::Point, cv::Point);
	void preDetection(cv::Mat&);

	cv::Mat getObjectHistogram();
	cv::Rect getCropRectangle();

protected:
	// Histogram hesaplamada, preObjectDetection ve objectDetection class larinda ortak kullanilan standart sabit degerlerdir
	int histSize[1] = { 64 };
	int channels[1] = { 0 };
	float range1[2] = { 0, 180 };
	const float* histRange[1] = { range1 };

private:
	void RGB2HSV(cv::Mat&);				// RGB -> HSV donusumunu yap
	void hsvMasking();					// HSV Matrisinde karanlik bolgelere maskeleme yap
	void calculateHistogram();			// Histogram hesapla
	void normalizeObjectHist();			// objectHist matrisini normalizle

	cv::Mat hsvFrame;					// Genel goruntunun hsv matrisi
	cv::Mat objectHist;					// Tespit edilen nesnenin histogrami
	cv::Rect cropRectangle;				// Secim yapilan bolgenin bilgilerini tutar
	cv::Mat blackZoneMask;				// Siyah bolgeleri maskelenmis matris
	cv::Mat cropHsvFrame, cropMask;		// hsvFrame ve blackZoneMask matrisleri uzerinden secim yapilan bolgeyi kes

	// hsvMasking() icin Scalar HSV maskeleme deger araliklari
	double lowH = 0, lowS = 30, lowV = 30;
	double highH = 180, highS = 255, highV = 255;
};



class ObjectDetection: protected PreObjectDetection
{
public:
	ObjectDetection();
	void resetObjectDetectionVariables();
	
	inline void RGB2HSV(cv::Mat& camFrame)
	{
		// orginal frame, donusum sonucu atanacak matris, donusum formati (BGR -> HSV)
		cvtColor(camFrame, hsvFrame, cv::COLOR_BGR2HSV);
	}
	inline void camShiftDetection(cv::Mat& camFrame, PreObjectDetection& preDetection)		// inline olarak tanýmlanmasi hiz kazandiricak
	{
		RGB2HSV(camFrame);						// camFrame nesnesine RGB -> HSV donusumu yap

		// Histogramýn Back Projeksiyonunu hesaplar.
		calcBackProject(&hsvFrame, numberOfSourceImage, channels, preDetection.getObjectHistogram(), outputBackProject, histRange);


		// camShift uygula -> Nesne histograminin arkadan izdusumu, aranacak goruntu, yinelemeli algoritma için durdurma kriterleri
		cv::RotatedRect rot_rect = CamShift(outputBackProject, preDetection.getCropRectangle(), cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10, 5));
		// Rotated Rectangle (Dondurulmus dikdortgen) turunde nesne return eder, bu nesnenin kordinatlarina eriserek belirlenen alan isaretlenebilir

		// anlik olarak bulunan noktalari detectionPoints dizisine aktarilir 
		rot_rect.points(detectionPoints);
		
	}
	void detectionDraw(cv::Mat&);				// tespit edilen nesneyi pencerede ciz
	int markDirectionsObject(cv::Mat& );		// tespit edilen nesnenin ekrandan tasmasi ve yonergelerin guncellemesi yapilir
	
	
private:
	int numberOfSourceImage = 1;		// islenecek kaynak frame sayisi
	cv::Point2f detectionPoints[4];		// Detection algoritmasi sonucunda tespit edilen noktalar
	cv::Mat outputBackProject;			// BackProjection hesaplamasi sonucu bu matrise aktarilir
	cv::Mat hsvFrame;					// Genel goruntunun hsv matrisi buraya islenir
};

