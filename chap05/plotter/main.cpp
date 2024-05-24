#include "plotter.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

void readFlightCurves(Plotter* plotter, const QString& fileName)
{
	const int numCurves = 6;
	const double factX = 0.0013;
	const double factY[numCurves] = {0.0008, 0.1, 0.2, 0.2, 0.1, 0.8};
	const double offsY[numCurves] = {500, -55, 309, 308, 0, 0};
	const int pos[numCurves] = {3, 6, 7, 8, 9, 10};

	QVector<QPointF> data[numCurves];
	QFile file(fileName);
	double offsX = 0.0;

	if (file.open(QIODevice::ReadOnly)) {
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			QStringList coords = line.split(' ', QString::SkipEmptyParts);
			if (coords.count() >= numCurves) {
				double x = factX * coords[0].toDouble();
				if (data[0].isEmpty())
					offsX = x;
				for (int i = 0; i < numCurves; ++i) {
					double y = coords[pos[i]].toDouble();
					data[i].append(
						QPointF(x - offsX, factY[i] * (y - offsY[i])));
				}
			}
		}

		for (int i = 0; i < numCurves; ++i) {
			plotter->setCurveData(i, data[i]);
		}
	}
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	Plotter plotter;
	plotter.setWindowTitle(QObject::tr("Plotter"));
#if 0
	readFlightCurves(&plotter, ":/in1.txt");
#else
	const int MaxY = 100;
	int numPoints = 100;
	int numCurves = 2;
	for (int i = 0; i < numCurves; ++i) {
		QVector<QPointF> curvePoints;
		for (int x = 0; x < numPoints; ++x) {
			curvePoints.append(QPointF(x, uint(qrand()) % MaxY));
		}
		plotter.setCurveData(i, curvePoints);
	}

	PlotSettings settings;
	settings.maxX = 100.0;
	settings.maxY = 100.0;
	plotter.setPlotSettings(settings);
#endif
	plotter.show();
	return app.exec();
}
