import argparse
import re
import cv2
import numpy as np
import os
from os import path
from glob import glob
from tqdm import tqdm

# uwu
# width -> cols 
# height -> rows
# channels -> depth

def read_lp(image_lp_path):
    with open(image_lp_path, "r") as img_file:
        shape = tuple(map(int, img_file.readline().strip().split()))
        if len(shape) != 3: raise ValueError("Formato inválido dimensiones incorrectas.")
        
        width, height, channels = shape
        image = np.zeros((height, width, 3), dtype="uint8")

        is_gray = channels == 1
        if is_gray:
            data = list(map(int, img_file.readline().strip().split()))
            for row in range(height):
                for col in range(width):
                    image[row, col, :] = data[row*width + col]
        else:
            for channel_i in range(channels):
                data = list(map(int, img_file.readline().strip().split()))
                for row in range(height):
                    for col in range(width):
                        image[row, col, channel_i] = data[row*width + col]       
    return image


def read_jpg(image_jpg_path):
    image = cv2.imread(image_jpg_path)[:,:,::-1] # bgr2rgb
    return image

def save_lp(image, image_jpg_path):
    height, width, channels = image.shape
    is_gray = np.all((image[:,:,0] == image[:,:,1]) & (image[:,:,1] == image[:,:,2]))
    if is_gray:
        channels = 1

    with open(image_jpg_path, "w") as img_file:
        img_file.write("{0} {1} {2}\n".format(width, height, channels))
        for channel_i in range(channels):
            img_channel = image[:,:,channel_i]
            for row in range(height):
                if row != 0: img_file.write(" ")
                for col in range(width):
                    if col != 0: img_file.write(" ")
                    img_file.write(str(img_channel[row, col]))
            img_file.write("\n")

def save_jpg(image, image_lp_path):
    image = image[:,:,::-1] # rgb2brg
    cv2.imwrite(image_lp_path, image) 


if __name__ == "__main__":
    # Argumentos de consola
    ap = argparse.ArgumentParser(
        description="Transforma imágenes entre formatos JPG y LP.")
    ap.add_argument("-i", "--inputs", nargs="+", type=str, required=False, default=None, 
                    help="Lista de imagenes de entrada.")
    ap.add_argument("-f", "--folder", type=str, required=False, default=None,
                    help="Ruta a carpeta con imagenes de entrada.")
    ap.add_argument("-o", "--output",  type=str, default="./",
                    help="Ruta de carpeta donde se guardarán las imágenes de salida.")
    ap.add_argument('--jpg', dest='jpg2lp', action='store_true', 
                    help="Usar formato de entrada jpg. Transformar de jpg a lp.")
    ap.add_argument('--lp', dest='lp2jpg', action='store_true', 
                    help="Usar formato de entrada lp. Transformar de lp a jpg.")
    ap.add_argument('--show-only', dest="skip", action='store_true',
                    help="Saltar la transformación y sólo mostrar las imágenes.")
    ap.add_argument('--show', dest='show', action='store_true', 
                    help="Mostrar imágenes.")
    args = vars(ap.parse_args())

    # Configuración
    input_images_paths = args["inputs"]
    input_folder_path = args["folder"]
    output_folder_path = args["output"]

    # Formatos
    lp2jpg = args["lp2jpg"]
    jpg2lp = args["jpg2lp"]

    # Mostrar
    skip = args["skip"]
    show = args["show"] or skip

    # Validación 
    # Se debe elegir uno de las dos transformaciones
    if lp2jpg == jpg2lp:
        ap.print_help()
        raise ValueError("Debe elegir uno de las dos opciones de formato.")
    # Se debe elegir una de las dos entreadas
    if (input_images_paths is None)  == (input_folder_path is None):
        ap.print_help()
        raise ValueError("Debe ingresar una lista de imágenes o una carpeta.")

    if (lp2jpg):
        src_image_format = ".lp"

    elif (jpg2lp):
        src_image_format = ".jpg"
        
    # Cargar images 
    if input_folder_path is not None:
        input_images_paths = glob(path.join(input_folder_path, "*" + src_image_format))
    else:
        input_images_paths = list(filter(lambda img: path.splitext(img)[1] == src_image_format, input_images_paths))

    if len(input_images_paths) == 0:
        ValueError("Input inválido, lista de imágenes vacía.")

    # Carpeta de salida
    if not os.path.exists(output_folder_path):
        ValueError("Carpeta de salida no existe")


    # De LP a JPG
    if src_image_format == ".lp":
        print("Formato de imágenes: JPG")
        print("Leyendo imágenes")
        images = [read_lp(img_src) for img_src in tqdm(input_images_paths)]
        total=len(images)
        
        if not skip:
            print("Transfomar imágenes a JPG")
            print("Guardando resultados en:", output_folder_path)
            output_images_paths = [path.basename(img_src) for img_src in input_images_paths]
            output_images_paths = [re.sub(r"\.lp$", ".jpg", img_src) for img_src in output_images_paths]
            output_images_paths = [path.join(output_folder_path, img_dst) for img_dst in output_images_paths]

            for image, image_dst in tqdm(zip(images, output_images_paths), total=total):
                save_jpg(image, image_dst)

    # De JPG a LP
    elif src_image_format == ".jpg":
        print("Formato de imágenes: JPG")
        print("Leyendo imágenes")
        images = [read_jpg(img_src) for img_src in tqdm(input_images_paths)]
        total=len(images)

        if not skip:
            print("Transfomar imágenes a LP")
            print("Guardando resultados en:", output_folder_path)
            output_images_paths = [path.basename(img_src) for img_src in input_images_paths]
            output_images_paths = [re.sub(r"\.jpg$", ".lp", img_src) for img_src in output_images_paths]
            output_images_paths = [path.join(output_folder_path, img_dst) for img_dst in output_images_paths]
            
            
            for image, image_dst in tqdm(zip(images, output_images_paths), total=total):
                save_lp(image, image_dst)

    if show:
        print("Mostrar imágenes")
        for image, image_src in tqdm(zip(images, input_images_paths), total=total):
            img_name = path.basename(image_src)
            if src_image_format == ".lp":
                image = image[:,:,::-1]
            cv2.imshow(img_name, image)
            cv2.waitKey(0)
    print("Done!")
