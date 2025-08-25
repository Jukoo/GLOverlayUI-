# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

os  = __import__("os") 
sys = __import__("sys")

sys.path.insert(0, os.path.abspath('.'))

project = 'GLOverlayUI'
copyright = '2025, Umar Ba <jUmarB@protonmail.com>'
author = 'Umar Ba <jUmarB@protonmail.com>'
release = 'v1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
        'breathe',
        ]

breathe_projects = {
            project: "./_doxy/xml"
        }
breathe_default_project = project 

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_logo="../assets/logo/gloverui.ico"
html_favicon=html_logo 
html_theme = 'pyramid'
html_static_path = ['_static']
