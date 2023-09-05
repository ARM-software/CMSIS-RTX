# RTX5 RTOS implementation

## Repository toplevel structure

```txt
  📦
  ┣ 📂 .github/workflows         GitHub Action workflows
     ┣ 📄 gh-pages.yml           Deployment of static documentation from gh-pages branch to GitHub Pages
     ┗ 📄 pack.yml               Generation/publish of the pack and documentation
  ┣ 📂 CMSIS                     CClass CMSIS files
     ┣ 📂 Documentation          Target directory for generated documentation
     ┣ 📂 DoxyGen                Source directory for documentation
        ┣ 📄 check_links.sh      Script to check generated html documentation for broken links
        ┗ 📄 gen_doc.sh          Documentation generation script
     ┗ 📂 RTOS2                  CGroup RTOS2 files
        ┣ 📂 RTX                 RTX implementation
           ┣ 📂 Config           Configuration file templates
           ┣ 📂 Examples         MDK uVision Example projects
           ┣ 📂 Examples_IAR     IAR Embedded Workbench Example projects
           ┣ 📂 Include          Public header files of RTX software component
           ┣ 📂 Library          Project files to build pre-built libraries
           ┣ 📂 Source           Private header and source files of RTX software component
           ┗ 📂 Template         User code template files
        ┗ 📂 Source              Generic RTOS2 source files
  ┣ 📄 ARM.CMSIS-RTX.pdsc        Pack description file
  ┗ 📄 gen_pack.sh               Pack generations script, see below
```

## Generating Software Pack

Some helper scripts are provided to generate the release artifacts from this repository.

### Doxygen Documentation

Generating the HTML-formatted documentation from its Doxygen-based source is done via

```bash
CMSIS-RTX $ ./CMSIS/DoxyGen/gen_doc.sh
```

After generating the documentation, one can check the html output for broken links:

```bash
CMSIS-RTX $ ./CMSIS/DoxyGen/check_links.sh
```

Prerequisites for these scripts to succeed are:

- Doxygen 1.9.6
- Python 3.9 or later with linkchecker package installed
  `pip install linkchecker`

### CMSIS-Pack Bundle

The CMSIS-Pack bundle can be generated with

```bash
CMSIS-RTX $ ./gen_pack.sh
```

Prerequisites for this script to succeed are:

- Generated documentation (see above)
- 7z
- packchk
- xmllint (optional)

### Version and Changelog Inference

The version and changelog embedded into the documentation and pack are inferred from the
local Git history. In order to get the full changelog one needs to have a full clone (not
a shallow one) including all release tags.

The version numbers are taken from the available annotated tags. The shown release dates and
changelogs are the tagger date and the associated message is.

## License

CMSIS-RTX is licensed under [Apache License 2.0](LICENSE).

## Contributions and Pull Requests

Contributions are accepted under Apache License 2.0. Only submit contributions where you have authored all of the code.

### Issues, Labels

Please feel free to raise an issue on GitHub
to report misbehavior (i.e. bugs)

Issues are your best way to interact directly with the maintenance team and the community.
We encourage you to append implementation suggestions as this helps to decrease the
workload of the very limited maintenance team.

We shall be monitoring and responding to issues as best we can.
Please attempt to avoid filing duplicates of open or closed items when possible.
In the spirit of openness we shall be tagging issues with the following:

- **bug** – We consider this issue to be a bug that shall be investigated.

- **wontfix** - We appreciate this issue but decided not to change the current behavior.

- **out-of-scope** - We consider this issue loosely related to CMSIS. It might be implemented outside of CMSIS. Let us know about your work.

- **question** – We have further questions about this issue. Please review and provide feedback.

- **documentation** - This issue is a documentation flaw that shall be improved in the future.

- **DONE** - We consider this issue as resolved - please review and close it. In case of no further activity, these issues shall be closed after a week.

- **duplicate** - This issue is already addressed elsewhere, see a comment with provided references.
