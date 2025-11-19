# Contributing to R-Type

## Getting started

read the documentation in `./doc` unsing `mdbook`

## Pull requests (PRs)
- Use a feature branch instead of the main branch

### Commit messages
Follow the conventional commits guidelines to make reviews easier and to make the VCS/git logs more valuable

```
type(scope): subject
```
- Prefix with a type:
    `build ci docs add feat fix refactor test`
- Append an optional (scope) such as (server), (client), …
- Use the imperative voice: "Fix bug" rather than "Fixed bug" or "Fixes bug."
- Keep it short (under 72 characters).

## Coding

### Lint

You can run the linter locally by:
```bash
make lint
```
### Style
You can format files by using:
```bash
make format
```
## Documentation

Read doc to understand the expected documentation style and conventions.

- [install mdbook](https://rust-lang.github.io/mdBook/guide/installation.html)

```bash
make doc # to build the documentation

make open_doc # to open the documetation on your default web browser
```
