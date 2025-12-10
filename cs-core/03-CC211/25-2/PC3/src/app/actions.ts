"use server";

import { revalidatePath } from "next/cache";
import {
  decrementSoldQuantity,
  deleteProduct,
  incrementSoldQuantity,
} from "@/lib/products";

export async function incrementProductQuantity(productId: number) {
  try {
    const result = await incrementSoldQuantity(productId);

    if (result) {
      revalidatePath("/");
      return { success: true };
    }

    return { error: "No se puede vender más productos. Stock agotado." };
  } catch (error) {
    console.error("Error incrementing quantity:", error);
    return { error: "Error al actualizar la cantidad" };
  }
}

export async function decrementProductQuantity(productId: number) {
  try {
    const result = await decrementSoldQuantity(productId);

    if (result) {
      revalidatePath("/");
      return { success: true };
    }
    return { error: "No se puede reducir más. La cantidad vendida ya es 0." };
  } catch (error) {
    console.error("Error decrementing quantity:", error);
    return { error: "Error al actualizar la cantidad" };
  }
}

export async function deleteProductFromDatabase(productId: number) {
  try {
    const result = await deleteProduct(productId);

    if (result) {
      revalidatePath("/");
      return { success: true };
    }
    return { error: "No se puede eliminar el producto." };
  } catch (error) {
    console.error("Error deleting product:", error);
    return { error: "Error al eliminar el producto" };
  }
}
