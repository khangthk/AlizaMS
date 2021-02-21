#ifndef SRWIDGET_H
#define SRWIDGET_H

#include "ui_srwidget.h"
#include <QCloseEvent>
#include <QStringList>
#include <QPrinter>

class SRImage;

class SRWidget: public QWidget, public Ui::SRWidget
{
Q_OBJECT
public:
	SRWidget(float);
	~SRWidget();
	void initSR(const QString&);
	QStringList tmpfiles;
	std::vector<SRImage> srimages;

protected:
	void closeEvent(QCloseEvent*) override;
	void readSettings();
	void writeSettings();

public slots:
	void preview_print(QPrinter*);
	void printSR();
	void saveSR();

private:
	QString tmpfile;
};

#endif // SRWIDGET_H
