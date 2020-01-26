#pragma once
#include"header.h"
#include<iostream>


#define ESC 27				// ESC -> ASCII code
#define KEYWAITTIME 100		// ESC tusunu okumasi icin tepki suresi (ms)
#define CAMINDEX 0
#define MAINWINDOWNAME "Frame"


// GLOBAL VARIABLES

enum steps { zeroStep = 0, downClickStep = 1, upClickStep = 2, detectionStep = 3 };		// baslangic durumu, mouse sol tusa basildi, mouse sol tus kalkti ve testip adimi
steps stepStatus = zeroStep;

bool button1Click = false;



struct classObjects
{
	Controls controlObject;
	ObjectDetection objectDetection;
	PreObjectDetection preObjectDetection;
	Mouse mouseObject;
	Display displayObject;
};

classObjects objects;

cv::VideoCapture cap(CAMINDEX);			// CAMINDEX li camera nesnesi yaratilir


cv::Mat camFrame;						// MAINWINDOWNAME goruntusu burada islenir		

void mouseCoord(int event, int x, int y, int flags, void* userdata) {

	// sol button basildiysa, baslangic noktasini tut
	if (event == cv::EVENT_LBUTTONDOWN) {
		objects.mouseObject.setStartPointX(x);
		objects.mouseObject.setStartPointY(y);
	}

	// mouse hareketli ve sol button basili iken
	else if (event == cv::EVENT_MOUSEMOVE && flags == cv::EVENT_FLAG_LBUTTON) {
		objects.mouseObject.setFinishPointX(x);
		objects.mouseObject.setFinishPointY(y);

		stepStatus = downClickStep;
	}

	// sol button kalktiginda frame kes
	else if (event == cv::EVENT_LBUTTONUP) {

		// bitis noktasi kordinatlari kontrollu sekilde guncellenir
		if (objects.mouseObject.getFinishPoint().x > camFrame.cols)
			objects.mouseObject.setFinishPointX(camFrame.cols);
		else
			if (objects.mouseObject.getFinishPoint().x < 0)
				objects.mouseObject.setFinishPointX(0);
						
		
		// bu kontroller ekran disi isaretlemeye karsi
		if (objects.mouseObject.getFinishPoint().y > camFrame.rows)
			objects.mouseObject.setFinishPointY(camFrame.rows);
		
		else
			if (objects.mouseObject.getFinishPoint().y < 0)
				objects.mouseObject.setFinishPointY(0);
		
					
		stepStatus = upClickStep;				// nesne seçiminin bittiði adima gec
	}
}

namespace cppui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm icin ozet
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Olusturucu kodunu buraya ekle
			//

		}

	protected:

		/// <summary>
		///kullanilan tum kaynaklari temizleyin.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:


	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Panel^ panel1;




	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;


	private: System::ComponentModel::IContainer^ components;



	private:
		/// <summary>
		///Gerekli tasarimci degiskeni.
		/// </summary>

		





#pragma region Windows Form Designer generated code
		/// <summary>
		/// Tasarimci destegi icin gerekli metot - bu metodun 
		///icerigini kod duzenleyici ile degistirmeyin.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->AutoSize = true;
			this->button1->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Enabled = false;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->button1->Location = System::Drawing::Point(21, 509);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(256, 87);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Sec";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button3
			// 
			this->button3->AutoSize = true;
			this->button3->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->button3->Location = System::Drawing::Point(21, 416);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(528, 87);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Kamerayý Çalýþtýr";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// panel1
			// 
			this->panel1->AutoSize = true;
			this->panel1->Controls->Add(this->pictureBox4);
			this->panel1->Controls->Add(this->pictureBox3);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(7, 17);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(530, 355);
			this->panel1->TabIndex = 3;
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.BackgroundImage")));
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox4->Location = System::Drawing::Point(272, 139);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(188, 83);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.BackgroundImage")));
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox3->Location = System::Drawing::Point(80, 139);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(188, 83);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Location = System::Drawing::Point(80, 228);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(380, 90);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Location = System::Drawing::Point(80, 43);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(380, 90);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click_1);
			// 
			// groupBox1
			// 
			this->groupBox1->AutoSize = true;
			this->groupBox1->Controls->Add(this->panel1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(543, 399);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Movement Direction";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// button2
			// 
			this->button2->AutoSize = true;
			this->button2->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Enabled = false;
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->button2->Location = System::Drawing::Point(284, 509);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(265, 87);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Iptal";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->AutoSize = false;
			this->statusStrip1->BackColor = System::Drawing::Color::Transparent;
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 611);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->statusStrip1->Size = System::Drawing::Size(568, 26);
			this->statusStrip1->TabIndex = 6;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(190, 20);
			this->toolStripStatusLabel1->Text = L"Lütfen kamerayý çalýþtýrýn.";
			this->toolStripStatusLabel1->Click += gcnew System::EventHandler(this, &MyForm::toolStripStatusLabel1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(568, 637);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->MaximumSize = System::Drawing::Size(586, 684);
			this->MinimumSize = System::Drawing::Size(586, 684);
			this->Name = L"MyForm";
			this->Text = L"Object Tracking";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		
	
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)	// Kamerayi ac
	{
		
		objects.controlObject.camConnectionControl(cap, CAMINDEX);						// kamera baglantisini kontrol et

		objects.displayObject.createWindow(MAINWINDOWNAME);						// MAINWINDOWNNAME ismi ile pencere yarat
		
		button1->Enabled = true;												// Select button aktif et

		timer1->Start();														// Program dongusunu baslat

		button3->Enabled = false;												// Kamera acma butonunu kapat
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rightPicture_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox2_Enter(System::Object^ sender, System::EventArgs^ e) {


	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		 stepStatus = zeroStep;				// baslangic adimina don
		 /// yeniden secim icin kirli veriler temizlenir
		 pictureBoxSetDefaultBackColor();	
		 objects.mouseObject.resetMouseClickCoord();
		 objects.preObjectDetection.resetPreObjectDetectionVariables();
		 objects.objectDetection.resetObjectDetectionVariables();

		 button1->Enabled = false;		// button1 tiklanamaz
		 button2->Enabled = true;		// button2 tiklanabilir
		 button1Click = true;
		 toolStripStatusLabel1->Text = "Lutfen kameradan bir secim yapiniz.";
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		button1Click = false;
		button2->Enabled = false;			// button2 tiklanamaz
		button1->Enabled = true;			// button1 tiklanabilir yap
		toolStripStatusLabel1->Text = "Secim iptal edildi.";
		pictureBoxSetDefaultBackColor();
		stepStatus = zeroStep;					// baslangic adimina don
	}

	public: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

	
		objects.displayObject.videoCapture(cap, camFrame);			// goruntu kameradan okunup gerekli nesneye aktarildi

		if (button1Click)
		{
			cv::setMouseCallback(MAINWINDOWNAME, mouseCoord, NULL);		// mouse hareketlerini parametere olarak anlik mouseCoord fonksiyonuna aktar
			switch (stepStatus)
			{
			case downClickStep:
				toolStripStatusLabel1->Text = "Secim tamamlaniyor";
				objects.displayObject.drawRectangleDisplay(camFrame, objects.mouseObject );			// anlik olarak goruntu uzerinden kesme sinirlarini belirle, dikdortgen ciz
				break;

			case upClickStep:
				toolStripStatusLabel1->Text = "Secim tamamlandi";
				objects.mouseObject.mouseClickCoordSet();				// kirpma sonucu mouse hareketlerine gore secilen kordinatlar duzenlenir

				objects.preObjectDetection.setCropRectangle(objects.mouseObject.getStartPoint(), objects.mouseObject.getFinishPoint());
				objects.preObjectDetection.preDetection(camFrame);
			
				stepStatus = detectionStep;									// tespit adimina gec
				break;
			}
		}
		else {
			toolStripStatusLabel1->Text = "Secim yapmak icin once sec butonuna tiklayiniz";
		}
		
		if (stepStatus == detectionStep)
		{
			toolStripStatusLabel1->Text = "Nesne belirleniyor.";
			objects.objectDetection.camShiftDetection(camFrame, objects.preObjectDetection);					// objectDetection algoritmasi ile tespit et
			objects.objectDetection.detectionDraw(camFrame);													// tespit edilen nesnenin ekranda sýnýrlarý cizilir
			int selectedPicBox = 0;																				// Nesne hangi yonde ekrandan tasacak
			selectedPicBox = objects.objectDetection.markDirectionsObject(camFrame);							// tespit edilen nesnenin yonunu belirt
			selectPictureBoxAndDraw(selectedPicBox);																	// hangi okun kirmiziya boyanacagini sec ve boya
			toolStripStatusLabel1->Text = "Nesne belirlendi.";
		}

		objects.displayObject.showFpsDisplay(cap, camFrame);					// Kamera FPS degerini gorutuye aktar
		objects.displayObject.videoDisplay(camFrame, MAINWINDOWNAME);			// MAINWINDOWNNAME penceresine goruntuyu aktar 
		
		if (cv::waitKey(KEYWAITTIME) == ESC || objects.controlObject.isCamFrameEmpty(camFrame))		// esc basilana kadar ya da camera goruntusu alinmadiysa
		{
			cv::destroyAllWindows();																// acilan tum pencereleri yok et
			exit(EXIT_FAILURE);
		}
		
	}
	void selectPictureBoxAndDraw( int selectedPicBox ) {
		
		pictureBoxSetDefaultBackColor();
		switch (selectedPicBox)
		{
		case 1:
			pictureBox4->BackColor = BackColor.Red;
			break;
		case 2:
			pictureBox3->BackColor = BackColor.Red;
			break;
		case 3:
			pictureBox2->BackColor = BackColor.Red;
			break;
		case 4:
			pictureBox1->BackColor = BackColor.Red;
			break;
		default:
			break;
		}
	}
	void pictureBoxSetDefaultBackColor()
	{
		pictureBox1->BackColor = pictureBox1->DefaultBackColor;
		pictureBox2->BackColor = pictureBox2->DefaultBackColor;
		pictureBox3->BackColor = pictureBox3->DefaultBackColor;
		pictureBox4->BackColor = pictureBox4->DefaultBackColor;
	}

private: System::Void toolStripStatusLabel1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
};

}
