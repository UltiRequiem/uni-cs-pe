import { turso } from "@/clients/turso";
import type {
  CreateProductInput,
  Product,
  UpdateProductInput,
} from "@/types/product";

export async function getProducts() {
  const { rows } = await turso.execute("SELECT * FROM products");
  return rows as unknown as Product[];
}

export async function getProductById(id: number): Promise<Product | null> {
  const { rows } = await turso.execute({
    sql: "SELECT * FROM products WHERE id = ?",
    args: [id],
  });

  if (rows.length > 0) {
    return rows[0] as unknown as Product;
  }

  return null;
}

export async function createProduct(
  input: CreateProductInput,
): Promise<Product> {
  const { rows } = await turso.execute({
    sql: `INSERT INTO products (name, quantity_max, quantity_sold, price) 
          VALUES (?, ?, ?, ?) 
          RETURNING *`,
    args: [
      input.name,
      input.quantity_max,
      input.quantity_sold ?? 0,
      input.price,
    ],
  });

  const newProduct = rows[0] as unknown as Product;

  return {
    id: newProduct.id,
    name: newProduct.name,
    quantity_max: newProduct.quantity_max,
    quantity_sold: newProduct.quantity_sold,
    price: newProduct.price,
    created_at: newProduct.created_at,
    updated_at: newProduct.updated_at,
  };
}

export async function updateProduct(
  id: number,
  input: UpdateProductInput,
): Promise<Product | null> {
  const updates: string[] = [];
  const args: (string | number)[] = [];

  if (input.name !== undefined) {
    updates.push("name = ?");
    args.push(input.name);
  }

  if (input.quantity_max !== undefined) {
    updates.push("quantity_max = ?");
    args.push(input.quantity_max);
  }

  if (input.quantity_sold !== undefined) {
    updates.push("quantity_sold = ?");
    args.push(input.quantity_sold);
  }

  if (input.price !== undefined) {
    updates.push("price = ?");
    args.push(input.price);
  }

  if (updates.length === 0) {
    return getProductById(id);
  }

  updates.push("updated_at = strftime('%Y-%m-%dT%H:%M:%fZ','now')");
  args.push(id);

  const { rows } = await turso.execute({
    sql: `UPDATE products SET ${updates.join(", ")} WHERE id = ? RETURNING *`,
    args,
  });

  if (rows.length > 0) {
    return rows[0] as unknown as Product;
  }

  return null;
}

export async function deleteProduct(id: number): Promise<boolean> {
  const { rowsAffected } = await turso.execute({
    sql: "DELETE FROM products WHERE id = ?",
    args: [id],
  });

  return rowsAffected > 0;
}

export async function incrementSoldQuantity(
  id: number,
  amount: number = 1,
): Promise<Product | null> {
  const { rows } = await turso.execute({
    sql: `UPDATE products 
          SET quantity_sold = quantity_sold + ?, 
              updated_at = strftime('%Y-%m-%dT%H:%M:%fZ','now')
          WHERE id = ? AND quantity_sold + ? <= quantity_max
          RETURNING *`,
    args: [amount, id, amount],
  });

  if (rows.length > 0) {
    return rows[0] as unknown as Product;
  }

  return null;
}

export async function decrementSoldQuantity(
  id: number,
  amount: number = 1,
): Promise<Product | null> {
  const { rows } = await turso.execute({
    sql: `UPDATE products 
          SET quantity_sold = quantity_sold - ?, 
              updated_at = strftime('%Y-%m-%dT%H:%M:%fZ','now')
          WHERE id = ? AND quantity_sold - ? >= 0
          RETURNING *`,
    args: [amount, id, amount],
  });

  if (rows.length > 0) {
    return rows[0] as unknown as Product;
  }

  return null;
}

export function serializeProduct(products: Product[]) {
  const serializedProducts = products.map((product) => ({
    ...product,
    created_at:
      typeof product.created_at === "string"
        ? product.created_at
        : product.created_at.toISOString(),
    updated_at:
      typeof product.updated_at === "string"
        ? product.updated_at
        : product.updated_at.toISOString(),
  }));

  return serializedProducts;
}
