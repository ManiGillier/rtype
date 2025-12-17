# Contributing to R-Type

## Getting started

read the documentation in `./doc` unsing `mdbook`

## Pull requests (PRs)
- Use a feature branch instead of the main branch
- All final pull requests are made toward the `dev` branch.
- The main branch should be untouched.

### Commit messages
Follow the conventional commits guidelines to make reviews easier and to make the git logs more valuable

```
[TYPE](scope) Message
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

BEWARE, formating applies on all files ! Don't modify someone else's code without approval.

## Documentation

Read the documentation to understand the expected documentation style and conventions.

- [install mdbook](https://rust-lang.github.io/mdBook/guide/installation.html)

```bash
make doc # to build the documentation

make open_doc # to open the documetation on your default web browser
```

The documentation is automatically deploied as github pages whenever present on the `dev` branch.

## Continuous Integration

We have github CI pipeline to show compilation status.  
We allow for non-compiling code, but we prefer not to merge it to the development branch.

We also automatically push a copy of this repository to our home Epitech repository (private).

## Continuous Deployment

To trigger a deployment, you need to create a tag with the format `{vB}[0-9]*.[0-9]*.[0-9]*` (as a regular expression).

This deployment will take the linked commit of this tag, compile the project, and if it does compile, push this commit as the new main reference, and add the compiled binaries to a new release with the tag content as release content.
