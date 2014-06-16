;;
;; init.el
;;

;; Language.
(set-language-environment 'Japanese)

;; Coding system.
(set-default-coding-systems 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-terminal-coding-system 'utf-8)
(set-buffer-file-coding-system 'utf-8)
(prefer-coding-system 'utf-8)

;; Package Manegement
(require 'package)
(add-to-list 'package-archives '("melpa" . "http://melpa.milkbox.net/packages/") t)
(add-to-list 'package-archives '("marmalade" . "http://marmalade-repo.org/packages/"))
(package-initialize)

;; usable evil
(require 'evil)
(evil-mode 1)

;; define el-get repository
(setq el-get-sources
      '(
        (:name evil-plugins
               :type github
               :pkgname "tarao/evil-plugins")
        ))

;; el-get basic setting
(add-to-list 'load-path "~/.emacs.d/el-get/el-get")

(unless (require 'el-get nil 'noerror)
  (with-current-buffer
      (url-retrieve-synchronously
       "https://raw.github.com/dimitri/el-get/master/el-get-install.el")
    (let (el-get-master-branch)
      (goto-char (point-max))
      (eval-print-last-sexp))))

(el-get 'sync)

;; auto install package.el
(require 'cl)
(defvar installing-package-list
  '(
    ;; package list
    evil
    evil-leader
    evil-numbers
    evil-nerd-commenter
    ))
(let ((not-installed (loop for x in installing-package-list
                            when (not (package-installed-p x))
                            collect x)))
  (when not-installed
    (package-refresh-contents)
    (dolist (pkg not-installed)
        (package-install pkg))))

;; auto install el-get.el
(defvar my/el-get-packages
  '(
    evil-plugins
    )
  "A list of packages to install from el-get at launch.")

(el-get 'sync my/el-get-packages)

;;
;; Plugin
;;


