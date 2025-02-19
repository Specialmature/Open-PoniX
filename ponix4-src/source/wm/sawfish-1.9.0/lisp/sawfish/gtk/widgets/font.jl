;; nokogiri-widgets/font.jl -- font selection widget
;;
;; Copyright (C) 2000 John Harper <john@dcs.warwick.ac.uk>
;;
;; This file is part of sawfish.
;;
;; sawfish is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.
;;
;; sawfish is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with sawfish; see the file COPYING.  If not, write to
;; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

(define-structure sawfish.gtk.widgets.font

    (export )

    (open rep
          rep.system
          gui.gtk-2.gtk
          sawfish.gtk.widget
          sawfish.wm.util.font)

  ;; FIXME: this is broken, in that only if Xrender is present
  ;; does gdk use Xft. But, it's the best I can do..
  (define use-xft (let ((x (getenv "GDK_USE_XFT")))
		    (or (not x) (/= (string->number x) 0))))

  ;; defined by configure
  (define have-pango-xft (eq 'yes 'yes))

  (define default-font (if use-xft "Sans" "fixed"))

  (define (make-font-item changed-callback)
    (let* ((button (gtk-font-button-new)))

      (gtk-font-button-set-use-font button t)
      (gtk-widget-set-size-request button 150 -1)

      (when changed-callback
	(g-signal-connect
	 button "font-set" (make-signal-callback changed-callback)))

      (gtk-widget-show button)

      (lambda (op)
	(case op
	  ((set) (lambda (x)
		   (cond ((stringp x)
			  (gtk-font-button-set-font-name button x))
			 ((consp x)
			  (let ((face (cond
                                       ((string-equal (car x) "Xft")
                                        (xft-description->face (cdr x)))
                                       ((string-equal (car x) "xlfd")
                                        (xlfd-description->face (cdr x)))
                                       ((string-equal (car x) "pango")
                                        (pango-description->face (cdr x))))))
			    (when face
			      (gtk-font-button-set-font-name
			       button (face->pango-description face)))))
			 (t (gtk-font-button-set-font-name button default-font)))))
	  ((clear) (lambda ()
		     (gtk-font-button-set-font-name button default-font)))
	  ((ref) (lambda ()
		   (let* ((pango-name (gtk-font-button-get-font-name button))
			  (face (pango-description->face pango-name)))
		     (cond ((not face) nil)
			   (use-xft
			    (if have-pango-xft
				(cons "Pango" (face->pango-description face))
			      (cons "Xft" (face->xft-description face))))
			   (t (cons "xlfd" (face->xlfd-description face)))))))
	  ((gtk-widget) button)
	  ((validp) (lambda (x) (stringp x)))))))

  (define-widget-type 'font make-font-item))
