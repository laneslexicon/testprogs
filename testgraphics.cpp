#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QTextStream>
#include <QFile>
#include <ostream>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
class MyItem : public QGraphicsTextItem {
public:
  MyItem(QGraphicsItem * parent = 0);
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent * event);
  void paint( QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w);
};
MyItem::MyItem(QGraphicsItem * parent) : QGraphicsTextItem(parent) {

}
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent * /* event */) {
  QTextCursor c = this->document()->find("out");
  if (c.isNull()) {
    return;
  }
  QTextCursor d = this->textCursor();
  qDebug() << d.charFormat().background().color().name();
//  c.movePosition(QTextCursor::NextCharacter,QTextCursor::KeepAnchor,3);

//  c.setCharFormat(fmt);
//  c.select(QTextCursor::WordUnderCursor);

  QTextCharFormat fmt = c.charFormat();
  qDebug() << "Position" << c.position();
  qDebug() << "Background" << fmt.background().color().name();
  qDebug() << "Foreground" << fmt.foreground().color().name();
  //  c.clearSelection();
  this->setTextCursor(c);
}
void MyItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w) {
/*
  qDebug() << Q_FUNC_INFO << painter->background().color().name();
  qDebug() << "Window" <<   o->palette.brush(QPalette::Window).color().name();
  qDebug() << "WindowText" <<   o->palette.brush(QPalette::WindowText).color().name();
  */
  QGraphicsTextItem::paint(painter, o, w);
}

int main(int argc, char** argv)
{
  QApplication app (argc, argv);
  QGraphicsScene myScene;

  //  QGraphicsTextItem* item = new QGraphicsTextItem;
  MyItem * item = new MyItem;
  if (0) {
  QFile f("input.css");
  QString css;
  if ( f.open(QIODevice::ReadOnly)) {
    QTextStream in(&f);
    in.setCodec("UTF-8");
    css = in.readAll();
    f.close();
  }
  QFile htmlsource("input.html");
  QString html;
  if ( htmlsource.open(QIODevice::ReadOnly)) {
    QTextStream in(&htmlsource);
    in.setCodec("UTF-8");
    html = in.readAll();
    htmlsource.close();
  }
  }
  item->setTextWidth(300);
  item->document()->setDefaultStyleSheet(".test { background-color: gray}");
  item->setHtml("<html><body class=\"test\"><p>hello world</p></body></html>");


//  const QRectF childRect = childItem->boundingRect();
 // childItem->setPos (-0.5 * childRect.width(), -0.5 * childRect.height());

  item->setToolTip ("Item ToolTip");
  myScene.addItem(item);

  QGraphicsView myView (&myScene);
  myView.move(400,400);
  //  myView.setCaption ("Test Nested QGraphicsItems ToolTips");
  myView.setAttribute (Qt::WA_AlwaysShowToolTips);
  myView.resize (420, 200);
  myView.show();

  return app.exec();
}
