#include "m_rng.h"
#include "defs/d_common.h"
#include "defs/d_constants.h"

// Min value: 0
// Max value: 1023
// Every value appears only once
const u16 RNG_TABLE[1024] = {
     881,  314,  632,  622,  357,  972,  208,  893,
     692, 1016,  119,  197, 1005,  424,  203,  296,
     951,   74,  269,  550,  426,  961,  414,  487,
     888,  140,  852,   19,  206,  642,  303,  470,
     878,  812,  618,  198,  887,  294,  691, 1019,
     210,  910,  675,  626,  974,  740,  664,  289,
     639,  551,  158,  567,  327,  539,  735,  167,
     305,  182,  137,  387,  138,  978,  159,  524,
     265,  409,  234,  682,  298,   31,  597,  867,
     673,  959,  737,  360,   34,  874,  870,  774,
     590,  143,  637,  947,  936,  802,  781,  501,
     160,   24,  797,  225,  750,  245,  584,  585,
     569, 1006,  398,  444,   15,  819,  762,  407,
     957,  589,  195,  243,  505,  408,   35,  736,
     826,  471,  942,  250,  227,  186,  677,  199,
     678,   37,  806,  344,  629,  311,  811,  765,
     530,  903,  389,  518,  239,  224,  727,   50,
    1014,  385,  411,  902,  625,  293,  316,  999,
     891, 1000,  347,  565,  815,  222,  490,  221,
     553,  286,  868,  196,  872,   95,  425,  480,
     129,  598,  631,  310,  528,  446,  561,  258,
     756,  184,  306,  983,  176,  218,  489,  754,
     237,  534,  659,  251,  842,  476,  869,  733,
     876,  442,  335,  896,  883,  662,  958,  871,
     169,  270,  134,  661,   39,  252,  945,  535,
     953,  704,  828,  454,  443,  482, 1018,  931,
     380,  300,  809,  515,  901,  803,  126,  111,
     465,  328,   53,  172,  556,  345,   81,  301,
     862,  544,   25,  843,  793,  547,  271,  382,
     900,  130,  404,  333,  917,  205,  180,   69,
     211,  946,   89,  722,  734,  320,  367,  193,
     509,  994,  832,  438,  859,  147,   88,  503,
     209,   14,  755,  499,  439,  164,  362,  749,
     697,  560,  474,  693,  361,  397,  512,  185,
     712,  135,  467,  721,   52,  840,  317,  645,
     694,  650,  498,  532,  276,  837,  400,  672,
     462,  101,  580,    7,  771,  578,  861,  479,
     139,  905,  415,  283,  517,  595,  372,  571,
     115,  152,  429,   33,   98,  738,  821,  641,
     970,  108,  514,  106,  973,  201,    9,  423,
     318,  991, 1017,  522,  545,  998,   67,  166,
     731,  110,  723,  897,   10,  458,  805,  410,
      57,  995,    1,  118,  351,  403,  785,  435,
     525,  349,  912,  717,  634,  212,  472,  226,
     851,  606,   13,  481,  764,  676,  332,   12,
     757,  434,  117,   23,   73,    0,  679,  798,
     280, 1013,  732,  801,  935,  548,  285,  892,
     363,  695,  557,  536,  940,  241,   85,  175,
     877,  123,  915,  422,  216,  777,  273,  213,
     538,  219,  521,  161,  441,  144,   54,  653,
     430,  743,  190,  253,  604,  768,   29,  266,
     202, 1015,  857,  287,  378,  552,  880,  633,
     608,  358,  165,  758,  315,  350,  187,  121,
     386,  325,  171,  960,  996,  644,  790,  865,
     984,  125,  529,  687,  619,   32, 1008,  703,
     436,  884,   72,  605,  249,   76,  630,  459,
     795,  549,  232,  769,   80,  304,  658,  937,
     127,  247,  680,  179,  379,  136,  275,  329,
     789,  413,  779,  508,  725,  461,  151,  856,
    1010,  217,  374,  500,    8,  582,  204,  419,
     497,  730,  373,  523,  761,  823,  364,  817,
     772,  776,  274,  775,  786,  242,   11,  987,
     282,  394,  377,  952,  652,  238,  799,    4,
    1021,  156,  558,  402,   27, 1007,  854,  586,
     621, 1023,  384,   48,  485,  154,  401,  827,
     365,   61,  313,  290,  421,  162,   96,  907,
     559,  685,  244,  967,  714,  954,  699,  791,
     845,  930,  352,  610,  504,  392,  885,  255,
     254,  841,  904,  780,  847,  993,  949,  116,
     596,  720,  432,  986,  520,  962,  572,  448,
     261,  666,  463,  393,  359,  257,  788,  133,
      49,  726,  577,  120,  992,  388,  449, 1002,
     599,  417,  839,  864,  256,  593,  858,  194,
      47,  707,  343,  297,  437,  719,  944,  189,
     114,   59,  751,  866,  519,  894,   84,  624,
     113,  968,  752,  850,  191,  985,  715,  700,
     647,  277,   91,  131,  782,  563,  342,  648,
     964,  834,  568,   93,  988,  710,  591,  319,
     369,  330,  475,   16,  916,  395,  718,  338,
     609,  236,  971,   64,  778,  689,  540,   87,
     112,  587,  200,  965,   82,  183,  281,   62,
     122,  822,  220,  181,  773,  341,  340, 1022,
     496,  813,  268, 1020,   79,  835,  575,   22,
      78,   83,  399,  376,  263,  941,  456,    6,
     473,  649,  895,  607,   36,  494,  100,  433,
     955,  742,   58,  602,   43,  477,   68,  739,
     979,  493,  927,  760,  339,  594,  576,  308,
     651,  668, 1003,  554,  177,  371,  592,  818,
     192,  381,  729,  368,  336,  981,  428,  292,
      94,  510,  337,  346,  656,  686,  427,   28,
     178,  969,  643,  102,  989,  207,  698,  976,
     366,  665,  744,  620,  141,  688,  246,   40,
     921,  174,  460,  531,  860,  543,  511,  145,
     267,  132,   56,   63,  445,  671,  646,  627,
     541,  420,   18,  925,  370,    3,  406,  873,
     516,  564,  312, 1011,  307,  846,  918,  623,
     107,   86,  708,  302,  153,  555,  982,  148,
     405,  616,  383,   30,  478,  831,  810,   26,
     654,  681,  932,  455,  348,  278,  450,    5,
     537,  391,  919,  356,   38,  614,  783,  824,
    1004,  223,  613,   20,  638,  702,  262,  142,
     830,  321,  447,  770,   17,  235,   99,  353,
     507,  628,  259,   44,  170,  546,  923,  488,
     674,  464,  603,  288,   45,  124,  272,  149,
     412,   65,  753,  669,  938,  105,  264,  483,
     309,  696,  331,  566,  542,  825,  440,  583,
     601,  980,  683,  716,  354,  963,  452,  814,
     635,  836, 1001,  922,  612,  926,  956, 1009,
     913,  466,  709,  484,  660,  240,  109,  322,
     533,   66,  875,  728,  724,  966, 1012,  617,
     924,  324,  848,  574,   51,  914,  833,  146,
     396,  943,  636,  939,  228,  747,  853,  491,
     562,  792,   21,  863,  763,  469,  990,  787,
     579,  215,  745,  526,  670,  899,  928,  741,
     457,  486,  157,   77,  746,  418,  934,  977,
     581,  800,  375,  260,  103,  502,  816,  431,
     231,   75,  808,  416,  898,  909,  784,   55,
     334,  911,   42,  933,  890,  920,  701,  390,
     188,  229,  975,  948,   97,  468,  279,  355,
     849,  855,  248,   41,  155,  655,  230,  663,
     759,  908,  796,  640,  233,  495,  168,  588,
     705,  748,   92,   60,  527,  173,  214,  706,
     804,  600,  766,  711,  879,  829,  906,  615,
     690,  570,  657,  950,  128,  820,  889,   71,
     323,  807,  492,    2,  295,  506,  684,  713,
     451,  767,  886,   90,  573,  838,  794,   46,
     513,  150,  284,   70,  611,  453,  882,  667,
     844,  299,  104,  291,  163,  997,  326,  929
};

u16 grindx = 0;
u16 lrindx = 0;

u16 rng_gnext(void) {
    return RNG_TABLE[grindx++ & BITMASK_12];
}

u16 rng_lnext(void) {
    return RNG_TABLE[lrindx++ & BITMASK_12];
}

void rng_reset(void) {
    grindx = 0;
    lrindx = 0;
}