��       W     �     �      �   �  �   ,  �   5  �   N  �   7  	6   \  	n   _  	�   `  
+   u  
�   l     b  o   V  �   Y  )   ~  �   �     �  �   %  M     s     �     �   e  �     '     ;     R     o     �   $  �     �     �     �             #  .     R     m     u     �     �     �     �   H  �          .     M   !  k     �     �   (  �     �     �   #       5     O   $  o     �     �   #  �   B  �   2  4     g      {     �     �   *  �   *       /     O     _   #  m   #  �   &  �     �     �   ,  
     7     P   -  e     �     �     �     �     �     �               3  �  N  �  �   j  �   u  0   �  �   �  :   �  �   �  D   �  �   �  �   �  O   �     �  �   �   R   �   �   �  !�  �  "�   9  $c   6  $�   )  $�   6  $�   �  %5     &   *  &-   >  &X   ?  &�   8  &�   H  '   )  'Y   1  '�   4  '�     '�   L  (
   I  (W   5  (�     (�   C  (�     ),     )I     )f     )�   �  )�   5  *%   ;  *[   3  *�   V  *�   1  +"   7  +T   t  +�   p  ,   K  ,r   @  ,�   5  ,�   R  -5   d  -�   ]  -�   3  .K   B  .   �  .�   n  /N   .  /�   E  /�   ;  02   B  0n   Y  0�   ^  1   E  1j     1�     1�   A  1�   A  2$   T  2f   3  2�   L  2�   o  3<   7  3�   -  3�   s  4     4�     4�     4�   !  4�   -  4�     5#   .  5<   .  5k   T  5�             >          	   0                 7      D   %   J             L      
   .   F   M           @   G       ;   =                      S   9   5          ,   C                 B   (   O       -                          :                      K   4               N   /              +       V                '             Q                     A   8       &   P   W   I   2   H      $              "   #   6   <   U       R      )   *       E   ?      3   T   !   1       
If no -e, --expression, -f, or --file option is given, then the first
non-option argument is taken as the sed script to interpret.  All
remaining arguments are names of input files; if no input files are
specified, then the standard input is read.

       --help     display this help and exit
       --version  output version information and exit
   --follow-symlinks
                 follow symlinks when processing in place
   --posix
                 disable all GNU extensions.
   -R, --regexp-perl
                 use Perl 5's regular expressions syntax in the script.
   -b, --binary
                 open files in binary mode (CR+LFs are not processed specially)
   -e script, --expression=script
                 add the script to the commands to be executed
   -f script-file, --file=script-file
                 add the contents of script-file to the commands to be executed
   -i[SUFFIX], --in-place[=SUFFIX]
                 edit files in place (makes backup if extension supplied)
   -l N, --line-length=N
                 specify the desired line-wrap length for the `l' command
   -n, --quiet, --silent
                 suppress automatic printing of pattern space
   -r, --regexp-extended
                 use extended regular expressions in the script.
   -s, --separate
                 consider files as separate rather than as a single continuous
                 long stream.
   -u, --unbuffered
                 load minimal amounts of data from the input files and flush
                 the output buffers more often
 %s
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE,
to the extent permitted by law.
 %s: -e expression #%lu, char %lu: %s
 %s: can't read %s: %s
 %s: file %s line %lu: %s
 : doesn't want any addresses E-mail bug reports to: <%s>.
Be sure to include the word ``%s'' somewhere in the ``Subject:'' field.
 GNU sed version %s
 Invalid back reference Invalid character class name Invalid collation character Invalid content of \{\} Invalid preceding regular expression Invalid range end Invalid regular expression Memory exhausted No match No previous regular expression Premature end of regular expression Regular expression too big Success Trailing backslash Unmatched ( or \( Unmatched ) or \) Unmatched [ or [^ Unmatched \{ Usage: %s [OPTION]... {script-only-if-no-other-script} [input-file]...

 `e' command not supported `}' doesn't want any addresses based on GNU sed version %s

 can't find label for jump to `%s' cannot remove %s: %s cannot rename %s: %s cannot specify modifiers on empty regexp cannot stat %s: %s command only uses one address comments don't accept any addresses couldn't attach to %s: %s couldn't edit %s: is a terminal couldn't edit %s: not a regular file couldn't follow symlink %s: %s couldn't open file %s: %s couldn't open temporary file %s: %s couldn't write %d item to %s: %s couldn't write %d items to %s: %s delimiter character is not a single-byte character error in subprocess expected \ after `a', `c' or `i' expected newer version of sed extra characters after command invalid reference \%d on `s' command's RHS invalid usage of +N or ~N as first address invalid usage of line address 0 missing command multiple `!'s multiple `g' options to `s' command multiple `p' options to `s' command multiple number options to `s' command no input files no previous regular expression number option to `s' command may not be zero option `e' not supported read error on %s: %s strings for `y' command are different lengths super-sed version %s
 unexpected `,' unexpected `}' unknown command: `%c' unknown option to `s' unmatched `{' unterminated `s' command unterminated `y' command unterminated address regex Project-Id-Version: GNU sed 4.2.0
Report-Msgid-Bugs-To: bug-gnu-utils@gnu.org
POT-Creation-Date: 2009-04-30 10:58+0200
PO-Revision-Date: 2008-11-28 00:00+0000
Last-Translator: Simos Xenitellis <simos.lists@googlemail.com>
Language-Team: Greek <team@lists.gnome.gr>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms:  nplurals=2; plural=(n != 1);
 
Αν δεν υπάρχουν επιλογές -e, --expression, -f ή --file, τότε το πρώτο
όρισμα που δεν είναι επιλογή αποτελεί το όνομα του προγρ. εντολών.
Όλα τα υπόλοιπα ορίσματα είναι ονόματα αρχείων εισόδου· αν δεν έχουν
καθοριστεί αρχεία εισόδου, τότε γίνεται ανάγνωση της κανονικής εισόδου.

       --help     εμφάνιση αυτού του κειμένου βοηθείας και έξοδος
       --version  εμφάνιση πληροφοριών έκδοσης προγράμματος και έξοδος
   --follow-symlinks
                 ακολούθηση συμβολικών συνδέσμων στην επιτόπια επεξεργασία
   --posix
                 απενεργοποίηση όλων των επεκτάσεων GNU στο πρωτότυπο sed.
   -R, --regexp-perl
                 χρήση κανονικών εκφράσεων με σύνταξη Perl 5 στο σενάριο.
   -b, --binary
                 άνοιγμα αρχείων ως δυαδικά (οι χαρακτήρες CR και LF δεν έχουν ειδική σημασία)
   -e σενάριο --expression=σενάριο
                 προσθήκη του σεναρίου στις εντολές προς εκτέλεση
   -f αρχείο-σεναρίου --file=αρχείο-σεναρίου
                 προσθήκη του αρχείου-σεναρίου στις εντολές προς εκτέλεση
   -i[ΕΠΙΘΗΜΑ], --in-place[=ΕΠΙΘΗΜΑ]
                 επιτόπια επεξεργασία (δημιουργίας αντιγράφου αν παρέχεται ΕΠΙΘΗΜΑ)
   -l N, --line-length=N
                 καθορισμός επιθυμητού μήκους γραμμής για αναδίπλωση γραμμών στην εντολή `l'
   -n, --quiet, --silent
                 δεν γίνεται αυτόματη εκτύπωση του χώρου υποδείγματος
   -r, --regexp-extended
                 χρήση επεκτεταμένων κανονικών εκφράσεων στο σενάριο.
   -s, --separate
                 τα αρχεία εισόδου να λογίζονται ξεχωριστά, αντί ως ένας
                 συνεχής μακρύς χείμαρρος.
   -u, --unbuffered
                 φόρτωση ελαχίστων ποσοτήτων δεδομένων από τα αρχεία εισόδου
                 και άδειασμα των ενταμιευτών εξόδου συχνότερα
 %s
Αυτό το πρόγραμμα είναι ελεύθερο λογισμικό· δείτε τον πηγαίο κώδικα για τους
κανονισμούς αντιγραφής. Δεν υπάρχει KAMMIA ΕΓΓΥΗΣΗ· ούτε ακόμα για
ΛΕΙΤΟΥΡΓΙΚΟΤΗΤΑ ή ΚΑΤΑΛΛΗΛΟΤΗΤΑ ΓΙΑ ΕΝΑ ΣΥΓΚΕΚΡΙΜΕΝΟ ΣΚΟΠΟ, μέχρι το σημείο
που επιτρέπει ο νόμος.
 %s: -e έκφραση #%lu, χαρακτήρας %lu: %s
 %s: αδυναμία ανάγνωσης του %s: %s
 %s: αρχείο %s γραμμή %lu: %s
 : δεν χρειάζονται διευθύνσεις Αναφορές σφαλμάτων μέσω ηλεκτρονικού ταχυδρομείου στο: <%s>.
Προσέξτε να συμπεριλάβετε τη λέξη ``%s'' κάπου στο πεδίο ``Subject:''.
 GNU sed έκδοση %s
 Μη έγκυρη οπισθαναφορά Μη έγκυρο όνομα κλάσης χαρακτήρων Μη έγκυρος χαρακτήρας ταξινόμησης Μη έγκυρο περιεχόμενο εντός \{\} Μη έγκυρη προηγούμενη κανονική έκφραση Μη έγκυρο τέλος εύρους Μη έγκυρη κανονική έκφραση Εξάντληση διαθέσιμης μνήμης Κανένα ταίριασμα Δεν βρέθηκε προηγούμενη κανονική έκφραση Πρόωρος τερματισμός κανονικής έκφρασης Πολύ μεγάλη κανονική έκφραση Επιτυχία Τελευταίος χαρακτήρας η πισωκάθετος Αταίριαστο ( ή \( Αταίριαστο ) ή \) Αταίριαστο [ ή [^ Αταίριαστο \{ Χρήση: %s [ΕΠΙΛΟΓΗ]... {σενάριο-αν-δεν-υπάρχει-άλλο-σενάριο} [αρχείο-εισόδου]...

 η εντολή `e' δεν υποστηρίζεται το `}' δεν χρειάζεται διευθύνσεις βασισμένο στο GNU sed έκδοση %s

 αδυναμία εύρεσης ετικέττας για μετάβαση στο `%s' αδυναμία διαγραφής του %s: %s αδυναμία μετονομασίας του %s: %s δεν επιτρέπεται ο ορισμός διαμορφωτών σε κενή κανονική έκφραση αδυναμία ανάγνωσης εγγραφής για το %s στον κατάλογο αρχείων: %s η εντολή χρησιμοποιεί μόνο μια διεύθυνση τα σχόλια δεν δέχονται διευθύνσεις αδυναμία προσάρτησης στο %s: %s αδυναμία επεξεργασίας του %s: είναι τερματικό αδυναμία επεξεργασίας του %s: δεν είναι κανονικό αρχείο αδυναμία ακολούθησης του συμβολικού συνδέσμου %s: %s αδυναμία ανοίγματος του %s: %s αδυναμία ανοίγματος του αρχείου %s: %s αδυναμία εγγραφής %d στοιχείου στο %s: %s αδυναμία εγγραφής %d στοιχείων στο %s: %s ο χαρακτήρας διαχωριστής έχει μέγεθος μεγαλύτερο από ένα byte σφάλμα στη υποδιαδικασία απαιτείται \ μετά τις εντολές `a', `c' ή `i' αναμενόταν νεώτερη έκδοση του sed επιπλέον χαρακτήρες μετά την εντολή μη έγκυρη αναφορά \%d στο δεξί τμήμα της εντολής `s' δεν επιτρέπεται η χρήση των +N ή ~N ως πρώτη διεύθυνση ακατάλληλη χρήση διεύθυνσης γραμμής 0 λείπει η εντολή πολλαπλά `!' πολλαπλές επιλογές `g' στην εντολή `s' πολλαπλές επιλογές `p' στην εντολή `s' πολλαπλός αριθμητικές επιλογές στην εντολή `s' δεν υπάρχουν αρχεία εισόδου δεν βρέθηκε προηγούμενη κανονική έκφραση η αριθμητική επιλογή στην εντολή `s' δεν μπορεί να είναι μηδέν η επιλογή `e' δεν υποστηρίζεται σφάλμα ανάγνωσης στο %s: %s τα αλφαριθμητικά για την εντολή `y' είναι διαφορετικού μεγέθους super-sed έκδοση %s
 αναπάντεχο `,' αναπάντεχο `}' άγνωστη εντολή: `%c' άγνωστη επιλογή για το `s' αταίριαστο `{' μη τερματισμένη εντολή `s' μη τερματισμένη εντολή `y' μη τερματισμένη κανονικής έκφραση διεύθυνσης 