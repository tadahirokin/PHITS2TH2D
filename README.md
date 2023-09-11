# PHITS2TH2D
Two-dimensional figure of PHITS converter for ROOT
PHITSの出力（ANGEL形式）の２次元プロットをROOTの２次元ヒストグラム(TH2D)に詰めるマクロです

## Usage
First, edit the following the file path definition in PHITS2TH2D.cpp to suit your file,
まず、PHITS2TH2D.cppの以下の場所を自分のファイルパスと合うように変更してください。

'''cpp
   #define FILEPATH test.out
'''

and then, run the following command in Root terminal to draw TH2D histgram.
その後、以下のコマンドをRootのターミナルに打ち込めばTH2Dの二次元ヒストグラムが表示されます。

'''
   > .x PHITS2TH2D.cpp
'''

Note, the histogram has not been saved automatically. If necessary, save by yourself.
ただし、表示されたヒストグラムは自動では保存されないため、必要であれば自分自身で保存してください。
