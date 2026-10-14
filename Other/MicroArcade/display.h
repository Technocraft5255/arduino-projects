void display_menu(){
  lcd.clear();
  cursor_pos = 0;
  current_page = "menu";
  lcd.setCursor(0, 0);
  lcd.write(0x3E);
  lcd.setCursor(2, 0);
  lcd.print("Play");
  lcd.setCursor(2, 1);
  lcd.print("How to play");
  lcd.setCursor(2, 2);
  lcd.print("Options");
  lcd.setCursor(2, 3);
  lcd.print("Credits");
}
void display_credits(int cursor_position){ 
  int pos = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  if (cursor_position==0){lcd.print("Credit by Emilien ");lcd.setCursor(0,1);pos ++;}
  lcd.print("Mariau, copy not ");
  lcd.setCursor(0,pos+1);pos++;
  lcd.print("allowed");
  lcd.setCursor(0,pos+1);
  lcd.print("contact me to emilie");
  if (cursor_position==1){lcd.setCursor(0,3);lcd.print("n.mariau@gmail.com");}
}

