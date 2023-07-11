#ifndef QOICONV_H
#define QOICONV_H

const char *getfileextension(const char *fname);
void getpngfiles(const char *dirpath);
void qoiconv(const char *pngfpath, const char *qoifpath);

#endif
