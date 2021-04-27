#pragma once
#include <QtWidgets>

class W_edge;
class H_edge;

class Vertex {
private:
	double x, y, z;
	H_edge* edge;
	int index;
public:
	Vertex() { x = 0, y = 0, z = 0, edge = nullptr, index = 0; }
	Vertex(double x1, double y1, double z1, H_edge* ed, int ind) { x = x1, y = y1, z = z1, edge = ed, index = ind; }

	void setValues(double x1, double y1, double z1, H_edge* ed, int ind) { x = x1; y = y1; z = z1; edge = ed; index = ind; }
	void setPtr(H_edge* ed) { edge = ed; }
	double X() { return x; }
	double Y() { return y; }
	double Z() { return z; }
	int Index() { return index; }

};

class Face {
	H_edge* edge;
public:
	Face() { edge = nullptr; }
	void setPointer(H_edge* edge1) { edge = edge1; }
	H_edge* retEdge() { return edge; }

};


class H_edge {
	Vertex* vert_origin;
	Face* face;
	H_edge* edge_prev, * edge_next;
	H_edge* pair;
public:
	H_edge() { vert_origin = nullptr, face = nullptr, edge_prev = nullptr, edge_next = nullptr, pair = nullptr; }
	H_edge(Vertex* origin, Face* fac, H_edge* prev, H_edge* next, H_edge* parik) { vert_origin = origin; face = fac; edge_prev = prev; edge_next = next; pair = parik; }
	void setAllPtr(Vertex* origin, Face* fac, H_edge* prev, H_edge* next, H_edge* parik) { vert_origin = origin; face = fac; edge_prev = prev; edge_next = next; pair = parik; }
	Vertex* origin() { return vert_origin; }
	H_edge* prev() { return edge_prev; }
	H_edge* next() { return edge_next; }
	H_edge* paired() { return pair; }

};


class ViewerWidget :public QWidget {
	Q_OBJECT
private:
	QString name = "";
	QSize areaSize = QSize(0, 0);
	QImage* img = nullptr;
	QRgb* data = nullptr;
	QPainter* painter = nullptr;
	QVector<QPoint> points;
	QVector<QPoint> end; 
	QVector<QPoint> newend;
	QVector<QPoint> Pd;
	double dt = 0,degree = 0;
	int cpoint = 0,method = 0;
	QColor color;
	double F0 = 0, F1 = 0, F2 = 0, F3 = 0;
	double B0 = 0, B1 = 0, B2 = 0, B3 = 0;

	//---------------------------------------- Sphere var--------------------------------------//
	QVector<Vertex> tableVertex = QVector<Vertex>();
	QVector<H_edge> Hedges = QVector<H_edge>();
	QVector<Face> faces = QVector<Face>();
	QVector<Vertex> centers = QVector<Vertex>();
	double Fi = (1.0 + sqrt(5)) / 2;

public:
	ViewerWidget(QString viewerName, QSize imgSize, QWidget* parent = Q_NULLPTR);
	~ViewerWidget();
	void resizeWidget(QSize size);

	//Image functions
	bool setImage(const QImage& inputImg);
	QImage* getImage() { return img; };
	bool isEmpty();

	//Data functions
	QRgb* getData() { return data; }
	void setPixel(int x, int y, const QColor& color);
	void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
	bool isInside(int x, int y) { return (x >= 0 && y >= 0 && x < img->width() && y < img->height()) ? true : false; }

	//Get/Set functions
	QString getName() { return name; }
	void setName(QString newName) { name = newName; }

	void setPainter() { painter = new QPainter(img); }
	void setDataPtr() { data = reinterpret_cast<QRgb*>(img->bits()); }

	int getImgWidth() { return img->width(); };
	int getImgHeight() { return img->height(); };

	void clear(QColor color = Qt::white);

	void drawDDA(int x1, int y1, int x2, int y2,QColor col);
	void drawBresen(int x1, int y1, int x2, int y2, QColor col);
	void drawBresenCircle(int x1, int y1, int x2, int y2, QColor col);
	void drawCurve(QColor col, int meth);
	void setPoints(QPoint p);
	void clearButton();
	void drawHermite();
	void drawCoons();
	void drawBezier();
	void setFpolyn(double te);
	void setBpolyn(double te);
	void setHermiteFactor(double d,int p);
	void drawPoints();
	
	//------------------------------------Sphere functions-------------------------------------//
	void createSphere();
	void fillVertex();
	void fillHedges();
	void fillFaces();
	void saveToVTK();
	void findCenter();

public slots:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
};