# nm-otool

Ce projet consiste a reproduire les comportement des fonctions `nm` et `otool -t`.

Les options supportées par ft_nm sont:
  -u : affiche uniquement les symboles `undefined`
  -U : n'affiche pas les symboles `undefined`
  -j : affiche uniquement les noms des appels
  -g : affiche uniquement les symboles externes
  -- : arrete la lecture des flags et prends les arguments suivants en tant que fichiers (utile pour un executable dont le nom est `-p` par exemple).

ft_otool reproduit le comportement de la fonction `otool -t` et ne prends pas d'options.

Les architectures 64 bits, 32 bits ainsi que les fat sont supportées.

---------------------------

You have to recode the nm (with no options) and the otool command (exactly the same as otool -t)