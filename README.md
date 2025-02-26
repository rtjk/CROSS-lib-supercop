# CROSS-lib-supercop

A script to generate a [SUPERCOP][supercop]-compliant version of the [CROSS][repo_cross] signature scheme, from the NIST submission package.
```
python3 generate.py CROSS_submission_*.zip
zip --symlinks -r CROSS.zip crypto_sign
```

<!-- sources -->

[repo_cross]: https://github.com/CROSS-signature/CROSS-implementation
[supercop]: https://bench.cr.yp.to/supercop.html
