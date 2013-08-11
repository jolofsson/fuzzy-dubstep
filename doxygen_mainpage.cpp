/*
 Jim Olofsson
 Dataingenjörsprogrammet
 Örebro Universitet
 */


/** \mainpage
 * 
 * 
 * <h1>Diamond Hunter</h1>
 * <br>
 * <h2>Kapitel 1: Specifikation av Uppgift</h2><br>
 * <b>Grundideer f&ouml;r spelet</b>
 * <br>
 * Sj&auml;lva iden med detta spel &auml;r att styra en spelkarakt&auml;r till att f&aring;nga s&aring; m&aring;nga skatter (diamanter) som m&ouml;jligt. N&auml;r man 
 * lyckats f&aring;nga in alla diamanter innan tiden har l&ouml;pt ut s&aring; har man klarat av en niv&aring; i spelet. Sv&aring;righetsniv&aring;n i spelet &ouml;kar 
 * efter var femte niv&aring;. Det inneb&auml;r att ytterligare en till diamant l&auml;ggs upp p&aring; spelplan bland de redan existerande diamanterna. 
 * Vid niv&aring; 10 s&aring; g&aring;r &auml;ven spelkarakt&auml;ren upp i niv&aring; och r&ouml;relsen p&aring; karakt&auml;ren f&ouml;rdubblas. Maximalt kan det finnas sju stycken 
 * diamanter samtidigt p&aring; spelplanen och tiden man har p&aring; sig att f&aring;nga in samtliga diamanter &auml;r konstant i hela spelet, d.v.s. 10 
 * sekunder. Lyckas man ej att f&aring;nga in alla diamanter innan tiden l&ouml;pt ut s&aring; har man f&ouml;rlorat.
 * <br>
 * <br>
 * <b>Gr&auml;nssnitt</b>
 * <br>
 * Vid start av programmet hamnar man i spelets huvudmeny. I menyn finns tre val som anv&auml;ndaren kan v&auml;lja bland och alla val sk&ouml;ts 
 * med hj&auml;lp av tangentbordet. Vid val 1. startas sj&auml;lva spelet. Val 2. visas "om"-spelet, d.v.s. information om hur man spelar 
 * och i vilket programmeringsspr&aring;k det &auml;r skapat i. Val 3. avslutar spelet. Man styr sin spelkarakt&auml;r med hj&auml;lp av tangentbordets 
 * piltangenter och n&auml;r en diamant plockas upp uppdateras spelarens po&auml;ng, och denna information finner man uppe till v&auml;nster i 
 * f&ouml;nstret. Nedr&auml;kning av tiden finner man centralt upptill i f&ouml;nstret. N&auml;r spelaren g&aring;r upp i niv&aring; uppdateras &auml;ven detta i ett 
 * f&auml;lt h&ouml;gst upp i f&ouml;nstret, d&auml;r man &auml;ven finner "high score" som uppdateras n&auml;r spelaren misslyckas med en niv&aring; (game over) och 
 * om po&auml;ngen spelaren har &auml;r h&ouml;gre &auml;n det nuvarande "high score". Om man vill avsluta ett aktivt spel trycker man p&aring; Esc-
 * tangenten.
 * <br>
 * <br>
 * <center>
 * <b>Sk&auml;rmdumpar</b><br><br>
 * Meny<br>
 * <img src="meny.jpg" width="320" height="240" />
 * <a href="meny.jpg">F&ouml;rstora bilden</a>
 * <br>
 * Spelplan<br>
 * <img src="spelet.jpg" width="320" height="240" />
 * <a href="spelet.jpg">F&ouml;rstora bilden</a>
 * <br>
 * Misslyckande<br>
 * <img src="gameover.jpg" width="320" height="240" />
 * <a href="gameover.jpg">F&ouml;rstora bilden</a>
 * </center>
 * <br>
 * <br>
 * <h2>Kapitel 2: Resultat och framtida f&ouml;rb&auml;ttringar</h2>
 * <br>
 * <b> Hur mycket hann vi implementera? </b>
 * <br>
 * Ett enkelt fungerande spel som &auml;r l&auml;tt att f&ouml;rst&aring;. Det som jag hann med att implementera var en spelkarakt&auml;r med 
 * r&ouml;relseanimation. Spelplan. M&aring;lobjekt i form av diamanter som spelkarakt&auml;ren skall plocka upp. Timer f&ouml;r nedr&auml;kning. Grafisk 
 * meny. Po&auml;ngr&auml;kning och h&ouml;gsta uppn&aring;dda po&auml;ng.
 * <br>
 * <br>
 * <b>Vad skulle kunna f&ouml;rb&auml;ttras?</b>
 * <br>
 * En mer dynamisk spelplan d&auml;r olika hinder skulle kunna orsaka att spelaren m&aring;ste ta andra v&auml;gar f&ouml;r att n&aring; diamanterna, d.v.s. 
 * mer utmanande. Även variation p&aring; skatter (inte bara diamanter) som ger olika po&auml;ng till spelaren. F&ouml;rutom det skulle man kunna 
 * f&ouml;rb&auml;ttra misslyckanden i spelet. Att man ist&auml;llet f&aring;r po&auml;ngavdrag n&auml;r man inte hinner plocka upp alla diamanter ist&auml;llet f&ouml;r 
 * att det blir game over direkt. Och d&auml;r s&auml;tta en gr&auml;ns till fem missade diamanter leder till ett misslyckande (game over).
 * <br>
 * <br>
 * <b>N&auml;sta version av programmet vad skulle det inneh&aring;lla j&auml;mf&ouml;rt med aktuell version</b>
 * <br>
 * <br>
 * N&auml;sta version hade jag t&auml;nkt mig att man skall kunna v&auml;lja om man vill spela med en annan spelare (allts&aring; tv&aring; spelare 
 * samtidigt). D&aring; finns det tv&aring; spelkarakt&auml;rer p&aring; spelplanen och som styrs med tangentbordet, d&auml;r spelarna t&auml;vlar om vem som 
 * plockar mest diamanter under en satt tid. F&ouml;rutom det skulle nog en hel del av det som finns under f&ouml;rb&auml;ttring implementeras 
 * ocks&aring;. Variation av skatter ger olika po&auml;ng, en del hinder som st&aring;r i v&auml;gen f&ouml;r spelaren.
 * <br>
 * <br>
 * <br>
 * <br>
 * <h6>Jim Olofsson<br>Dataingenj&ouml;rsprogrammet<br>&ouml;rebro Universitet</h6>
 * </center>
 */