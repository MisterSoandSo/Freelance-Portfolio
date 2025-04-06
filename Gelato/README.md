# Gelato API Order Debug Script

This is a minimal Python script created for a **contest submission** focused on debugging an order placement integration for the [Gelato](https://www.gelato.com) print API.

## ⚠️ Disclaimer

> **This script was written specifically for a code debugging contest and is provided _as-is_.**  
> It is not production-ready, and no warranties are made regarding correctness, completeness, or future support.

## Overview

The script demonstrates how to submit an order to the Gelato API using a predefined set of data including:

- Product details
- Customer and shipping information
- A direct link to a PDF print file

## ⚙️ Special Note on `productUid` and `pageCount`

The `productUid` specifies the exact print product you're ordering — e.g., a photobook with specific dimensions, paper type, binding, finish, etc.  
The `pageCount` refers to the number of **internal pages** that the product is designed for, **not** the number of pages in your uploaded file.

**Important:**
- For photobooks, Gelato expects 1 page in the PDF to be the **cover**, and the rest to match the specified `pageCount`.
- Example:
  - If you select a 36-page photobook, set `pageCount` to `36`.
  - Then upload a **37-page PDF** — 1 page for the cover, 36 pages for the content.

Incorrect values here can cause order failures or printing issues.