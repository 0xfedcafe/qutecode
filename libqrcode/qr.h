//
// Created by prise on 11/3/21.
//

#ifndef QUTECODE_LIBQRCODE_QR_H_
#define QUTECODE_LIBQRCODE_QR_H_

class QR {
  enum Level {   // Error-correction Level
    Low,         // 20%
    Medium,      // 38%
    MediumHigh,  // 55%
    High         // 65%
  };
};

#endif  // QUTECODE_LIBQRCODE_QR_H_
