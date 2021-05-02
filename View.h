#pragma once
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QOpenGLFunctions>
#include "Data.h"
#include <string>
#include <algorithm>
class View:public QOpenGLWidget
{
protected:
	Data data;
	int layer;

protected:
	
	void initializeGL()override
	{
		QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions(); 

		f->glClearColor(255,255,255,1);
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	void resizeGL(int nWidth, int nHeight)override
	{
		
		glMatrixMode(GL_PROJECTION);
		// загрузка единичной матрицы
		glLoadIdentity();
		// установка ортогонального преобразования
		glOrtho(0.0f, data.getWidth() - 1, 0.0f, data.getHeigth() - 1, -1.0f, 1.0f);
		// установка окна обзора
		glViewport(0, 0, nWidth, nHeight);
		update();
	}
	void paintGL()override
	{
		QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();  f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// очистка экрана


		f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		VisualizationQuads();
	
	}

	int TransferFunction(short value)
	{
		int c = (value - data.getMin()) * 255 / (data.getMax() - data.getMin());
		return c;
	}


	void View::VisualizationQuads()
	{
		QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();  f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		int c;
		int w = data.getWidth();
		int h = data.getHeigth();
		for (int y = 0; y < (h - 1); y++)
			for (int x = 0; x < (w - 1); x++)
			{
				glBegin(GL_QUADS);
				c = TransferFunction(data[layer * w * h + y * w + x]);
				glColor3i(c,c,c);
				glVertex2i(x, y);
				c = TransferFunction(data[layer * w * h + (y + 1) * w + x]);
				glColor3i(c, c, c);
				glVertex2i(x, (y + 1));
				c = TransferFunction(data[layer * w * h + (y + 1) * w + x + 1]);
				glColor3i(c, c, c);
				glVertex2i((x + 1), (y + 1));
				c = TransferFunction(data[layer * w * h + y * w + x + 1]);
				glColor3i(c, c, c);
				glVertex2i((x + 1), y);
				glEnd();
			}
	}

	void View::keyPressEvent(QKeyEvent* event)
	{
		if (event->nativeVirtualKey() == Qt::Key_Up)
		{
			layer= std::min(layer + 1, data.getDepth() - 1);
		}
		else if (event->nativeVirtualKey() == Qt::Key_Down)
		{
			layer = std::max(layer - 1, 0);
		}
		else if (event->nativeVirtualKey() == Qt::Key_N)
		{
			// Переключиться на следующий тип рендеринга
		}
		update();
	}
public:
	View() :layer(0) {}

	void LoadData(const std::string& s)
	{
		data.readFile(s);
	}
};

