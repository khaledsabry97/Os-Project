using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace ZedGraph;
using namespace std;

void CreateGraph(String ^fileName, double* x, double* y, int sizeX);

int main()
{
	int ySize = 9;
	int xSize = 2 * ySize;
	double* arrX = new double[xSize] {1, 4, 5, 8, 9, 10, 11, 14, 15, 18, 19, 22, 23, 24, 25, 26, 27, 28};
	double* arrY = new double[ySize] {1, 2, 3, 4, 5, 1, 2, 4, 1};
	CreateGraph("test.png", arrX, arrY, xSize);
	return 0;
}

void CreateGraph(String ^fileName , double* x, double* y, int sizeX){
	// get a reference to the GraphPane
	RectangleF rect = RectangleF(0, 0, 900, 600);
	GraphPane^ myPane = gcnew GraphPane(rect, "Pane Title", "X Title", "Y Title");
	// Set the Titles
	myPane->Title = "Schduling Processes";
	myPane->XAxis->Title = "Time";
	myPane->YAxis->Title = "Process Number";
	
	// Add gridlines to the plot, and make them gray
	myPane->XAxis->IsShowGrid = true;
	myPane->YAxis->IsShowGrid = true;
	myPane->XAxis->GridColor = Color::LightGray;;
	myPane->YAxis->GridColor = Color:: LightGray;

	int j = 0;
	for (int i = 0; i < sizeX; i++) {
		PointPairList^ list1 = gcnew PointPairList();
		list1->Add(x[i], y[j]);
		i++;
		list1->Add(x[i], y[j]);
		LineItem^ myCurve = myPane->AddCurve("Process",
			list1, Color::White, SymbolType::None);
		myCurve->IsLegendLabelVisible = false;
		myCurve->Line->Fill = gcnew Fill(Color::White, Color::Red, 45);
		j++;
	}

	// Fill the Axis and Pane backgrounds
	myPane->AxisFill = gcnew Fill(Color::White,
		Color::FromArgb(255, 255, 166), 90);
	myPane->AxisFill = gcnew Fill(Color::FromArgb(250, 250, 255));

	Bitmap^ bm = gcnew Bitmap(1, 1);
	Graphics^ g = Graphics::FromImage(bm);
	myPane->AxisChange(g);
	// Retrieve the image
	Image^ img = myPane->Image;
	// Save image as PNG
	img->Save(fileName, ImageFormat::Png);
}