import pandas as pd

name = 'kien'
sample = 'alphabet/a'
char = 'ijkl'
txt_folder_path = 'D:/for_work/vscode/workspace/hand_gesture_algorithm/chains/ijkl'
excel_foler_path = 'D:/for_work/vscode/workspace/hand_gesture_algorithm/chains/ijkl'

def convert2excel(txt_folder, excel_folder):
  for i in range(1, 4):
    txt_file = txt_folder + '/' + char + str(i) + '.txt'
    excel_file = excel_folder + '/' + char + str(i) + '.xlsx'
    txt_file = pd.read_table(txt_file, sep = ',')
    txt_file.to_excel(excel_file, 'Sheet1')

convert2excel(txt_folder_path, excel_foler_path)