#include <QCoreApplication>
#include <QDebug>
#include <QStringList>
#include <QTimer>
#include <QFile>
#include <iostream>
#include <string>
#include <sstream>

#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
static QStringList errors;
void parseErrorHandler(void *ctx, const char *msg, ...) {

  char string[512];
   va_list arg_ptr;

   va_start(arg_ptr, msg);
   vsnprintf(string, 512, msg, arg_ptr);
   va_end(arg_ptr);
   QString s = string;
   qDebug() << s.trimmed();
   errors << s.trimmed();
   qDebug() << "errors size" << errors.size();
  return;
}
QString getLastError(bool remove) {
  QString str;
  if (remove) {
    str = errors.takeLast();
  }
  else {
    str = errors.last();
  }
  return str;
}
void run() {
  xsltStylesheetPtr cur = NULL;
  xmlDocPtr doc, res;
  xmlSubstituteEntitiesDefault(1);
  xmlLoadExtDtdDefaultValue = 1;
  xmlGenericErrorFunc handler = (xmlGenericErrorFunc)parseErrorHandler;
  initGenericErrorDefaultFunc(&handler);
  cur = xsltParseStylesheetFile((const xmlChar *)"entry.xslt");
  if (cur == NULL) {
    qDebug() << "parse sheet error";
    //    emit(finished());
    return;
  }
  const char * params[16 + 1];
  memset(params,0x00,sizeof(params));
  params[0] = "entrytype";
  params[1] = "'free'";
  params[2] = NULL;

  doc = xmlParseFile("node.xml"); //("n9929.xml");
  if (doc != 0) {
    res = xsltApplyStylesheet(cur, doc, params);
    xsltSaveResultToFile(stdout, res, cur);
    xsltFreeStylesheet(cur);
    xmlFreeDoc(res);
    xmlFreeDoc(doc);
  }
  else {
    qDebug() << getLastError(true);
  }
  QFile f("entry.xslt");
  if (! f.open(QIODevice::ReadOnly)) {
    qDebug() << "cannot load xslt";
    //    emit(finished());
  }
  QTextStream in(&f);
  QString line;
  while( ! in.atEnd()) {
    line += in.readLine();
  }
  f.close();

  qDebug() << "Doing in memory test";
  QByteArray ar = line.toUtf8();
  xmlDocPtr xptr;
  xmlDocPtr inputDoc;
  xsltStylesheetPtr test;
  ///-----
  xptr = xmlParseMemory((const char *)ar.data(), ar.size());
  if (xptr == NULL) {
    qDebug() << "xmlparsememory problem";
  }
  //  xmlDocPtr xptr = xmlParseDoc((const xmlChar *)ar.data());
  test = NULL;
  test = xsltParseStylesheetDoc(xptr);
  inputDoc = xmlParseFile("node.xml"); //("n9929.xml");
  if (inputDoc != 0) {
    xmlDocPtr res = NULL;
    res = xsltApplyStylesheet(test, inputDoc, params);
    if (! res ) {
      qDebug() << "null result";
    }
    else {
      xsltSaveResultToFile(stdout, res, test);
    }
    xsltFreeStylesheet(test);
    xmlFreeDoc(res);
    xmlFreeDoc(inputDoc);
  }
  ///--------
  ///-----
  xptr = xmlParseMemory((const char *)ar.data(), ar.size());
  if (xptr == NULL) {
    qDebug() << "xmlparsememory problem";
  }
  //  xmlDocPtr xptr = xmlParseDoc((const xmlChar *)ar.data());
  test = NULL;
  test = xsltParseStylesheetDoc(xptr);
  inputDoc = xmlParseFile("node.xml"); //("n9929.xml");
  if (inputDoc != 0) {
    xmlDocPtr res = NULL;
    res = xsltApplyStylesheet(test, inputDoc, params);
    if (! res ) {
      qDebug() << "null result";
    }
    else {
      xsltSaveResultToFile(stdout, res, test);
    }
    xsltFreeStylesheet(test);
    xmlFreeDoc(res);
    xmlFreeDoc(inputDoc);
  }

  xsltCleanupGlobals();
  xmlCleanupParser();
  //  emit(finished());
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc,argv);

  QStringList cmdargs = QCoreApplication::arguments();

  // This will cause the application to exit when
  // the task signals finished.
  //  QObject::connect(&task, SIGNAL(finished()), &a, SLOT(quit()));
  //  QTimer::singleShot(0, &task, SLOT(run()));
  run();

  return 0;//a.exec();
}
