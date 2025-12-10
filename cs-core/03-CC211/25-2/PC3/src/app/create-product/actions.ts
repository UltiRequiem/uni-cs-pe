"use server";

import { createProduct } from "@/lib/products";
import type { CreateProductInput } from "@/types/product";

export async function createProductAction(formData: FormData) {
  try {
    const productData: CreateProductInput = {
      name: formData.get("name") as string,
      quantity_max: Number(formData.get("quantity_max")),
      price: Number(formData.get("price")),
      quantity_sold: Number(formData.get("quantity_sold")) || 0,
    };

    if (!productData.name.trim()) {
      return { error: "Product name is required" };
    }

    if (productData.quantity_max <= 0) {
      return { error: "Maximum quantity must be greater than 0" };
    }

    if (productData.price < 0) {
      return { error: "Price cannot be negative" };
    }

    if (
      productData.quantity_sold !== undefined &&
      (productData.quantity_sold < 0 ||
        productData.quantity_sold > productData.quantity_max)
    ) {
      return { error: "Sold quantity must be between 0 and maximum quantity" };
    }

    const newProduct = await createProduct(productData);

    return { success: true, product: newProduct };
  } catch (error) {
    console.error("Error creating product:", error);
    return { error: "Failed to create product. Please try again." };
  }
}
