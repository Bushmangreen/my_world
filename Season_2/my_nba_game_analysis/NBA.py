
"""
{"player_name": XXX, //string
   "MP": XXX, // Minutes Played,string
   "FG": XXX, // Field Goal same as FGM 
  "FGA": XXX, // Field goals attempted (both 2pts and 3 pts)
  "FG%": XXX, // Field goal percentage, FGM/FGA
   "3P": XXX, // 3 point field goal same as 3PM
  "3PA": XXX, // Average 3 point field goals attempted 
  "3P%": XXX, // 3 point field goal percentage (3PM/3PA)
   "FT": XXX, // free throw made same as FTM
  "FTA": XXX, // free throw attempted 
  "FT%": XXX, // free throw percentage FTM/FTA
  "ORB": XXX, // Offensive rebounds->The number of rebounds a player or team has collected while they were on offense
  "DRB": XXX, // Defensive Rebounds-> The number of rebounds a player or team has collected while they were on defense
  "TRB": XXX, // Total Rebounds
  "AST": XXX, // Assists->Pass that lead to a made basket
  "STL": XXX, // Steels->Number of times a defensive player or team takes the ball from a player on offense, causing a turnover
  "BLK": XXX, // Blocks->A block occurs when an offensive player attempts a shot, and the defense player tips the ball, blocking their chance to
  "TOV": XXX, // Turnover->A turnover occurs when the player or team on offense loses the ball to the defense
   "PF": XXX, // Personal Fouls->The number of personal fouls a player or team committed
  "PTS": XXX} // Points-> The number of points scored
  """

   "MP": XXX, // 
   "FG": XXX, #(\w\. [a-z]+)? (misses)? (2-pt|3-pt)
  "FGA": XXX, // 
  "FG%": XXX, // 
   "3P": XXX, # (\w\. [a-z]+)? (misses)? 3-pt
  "3PA": XXX, // 
  "3P%": XXX, // 
   "FT": XXX, # (\w\. [a-z]+)? (misses)? free throw (\d) of (\d)
  "FTA": XXX, // 
  "FT%": XXX, // 
  "ORB": XXX, # Offensive rebound
  "DRB": XXX, # Defensive rebound
  "TRB": XXX, // 
  "AST": XXX, # assist by (\w\. [a-z]+)
  "STL": XXX, # steal by (\w\. [a-z]+)
  "BLK": XXX, # block by (\w\. [a-z]+)
  "TOV": XXX, # turnover by (\w\. [a-z]+)
   "PF": XXX, # foul by (\w\. [a-z]+)
  "PTS": XXX // 







