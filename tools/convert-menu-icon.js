const sharp = require('sharp');
const fs = require('fs');
const path = require('path');

// Read the icon file
const iconPath = path.join(__dirname, '..', 'db-icon.png');
const iconBuffer = fs.readFileSync(iconPath);

// Pebble menu icons are typically 25x25 pixels
// Using fit: contain to ensure the full clock face is visible
async function convert() {
  const outputPath = path.join(__dirname, '..', 'resources', 'images', 'sbb-menu-icon.png');

  await sharp(iconBuffer)
    .resize(25, 25, { fit: 'contain', background: { r: 255, g: 255, b: 255, alpha: 0 } })
    .png()
    .toFile(outputPath);

  console.log(`Created sbb-menu-icon.png at ${outputPath}`);
  console.log('Conversion complete!');
}

convert().catch(console.error);
